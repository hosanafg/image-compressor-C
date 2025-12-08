/* 
******************************************************

Aluna: Hosana Fernandes Gomes
Matrícula: 20251045050585
Avaliação 04: Trabalho Final
04.505.23 − 2025.2 − Prof.Daniel Ferreira
Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
S.O: Windows 11

********************************************************
*/

#include "decoder.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa a estrutura BitStreamReader
BitStreamReader* create_bitstream_reader(char *filename) {
    BitStreamReader *bs = (BitStreamReader *)malloc(sizeof(BitStreamReader));
    if (!bs) exit(1);

    bs->fp = fopen(filename, "rb");
    if (!bs->fp) {
        perror("Erro ao abrir arquivo compactado para leitura");
        free(bs);
        exit(1);
    }

    bs->buffer = 0;
    bs->bit_count = 0;
    bs->is_loaded = 0; // O buffer ainda não foi carregado
    return bs;
}

// Fecha o arquivo e libera a memória da estrutura
void close_bitstream_reader(BitStreamReader *bs) {
    if (bs) {
        fclose(bs->fp);
        free(bs);
    }
}

// Lê um único bit do stream
int read_bit(BitStreamReader *bs) {
    // Carrega o próximo byte se o buffer estiver vazio ou se é a primeira leitura
    if (bs->bit_count == 0 && bs->is_loaded == 0) {
        if (fread(&(bs->buffer), sizeof(unsigned char), 1, bs->fp) != 1) {
            return -1; // Fim do arquivo ou erro
        }
        bs->bit_count = 8; // 8 bits disponíveis
        bs->is_loaded = 1;
    } 
    else if (bs->bit_count == 0 && bs->is_loaded == 1) {
        if (fread(&(bs->buffer), sizeof(unsigned char), 1, bs->fp) != 1) {
            // Se falhar ao ler um novo byte, e ainda temos que ler, é o final do arquivo.
            return -1; 
        }
        bs->bit_count = 8;
    }

    // Lê o bit mais significativo (esquerda) primeiro
    int bit = (bs->buffer >> 7) & 1; 

    // Move o buffer para a esquerda (descarta o bit lido)
    bs->buffer <<= 1;
    bs->bit_count--;

    return bit;
}

// Lê um valor de 8 bits (o valor do pixel)
unsigned char read_byte(BitStreamReader *bs) {
    unsigned char value = 0;
    for (int i = 0; i < 8; i++) {
        int bit = read_bit(bs);
        if (bit == -1) {
            // Em caso de erro na leitura, retornar 0 (ou lidar com o erro)
            fprintf(stderr, "Erro ao ler byte do bitstream: Fim inesperado do arquivo.\n");
            return 0;
        }
        // Constrói o byte, inserindo o bit da esquerda para a direita (MSB first)
        value = (value << 1) | bit;
    }
    return value;
}

// Lê os metadados (cabeçalho QCF)
void read_qcf_header(BitStreamReader *bs, struct pgm *pio) {
    // Lendo as dimensões (largura, altura, maxval) - Assumimos que são inteiros (4 bytes)
    fread(&(pio->c), sizeof(int), 1, bs->fp);
    fread(&(pio->r), sizeof(int), 1, bs->fp);
    fread(&(pio->mv), sizeof(int), 1, bs->fp);

    // Ajusta o ponteiro de arquivo para o início do bitstream (após o cabeçalho)
    // O fread avança o ponteiro, mas precisamos garantir que o próximo read_bit
    // comece a ler a partir do primeiro byte do bitstream.
    
    // O buffer deve ser limpo/recarregado após a leitura de bytes inteiros (cabeçalho).
    bs->buffer = 0;
    bs->bit_count = 0; 
    bs->is_loaded = 0; // Garante que o primeiro bit do bitstream seja lido corretamente
}

// ----------------------------------------------------
// Função principal: Descodificação Recursiva da Quadtree
// ----------------------------------------------------
QuadNode* decode_quadtree(BitStreamReader *bs, int total_width, int start_x, int start_y, int size) {
    
    int flag_bit = read_bit(bs);
    if (flag_bit == -1) return NULL; // Fim do arquivo
    
    QuadNode *node = (QuadNode *)malloc(sizeof(QuadNode));
    if (!node) exit(1);
    
    node->x = start_x;
    node->y = start_y;
    node->width = node->height = size;

    for (int i = 0; i < 4; i++) node->children[i] = NULL; 

    if (flag_bit == 1) { 
        // É Folha: Lê o valor do pixel (8 bits)
        node->is_leaf = 1; 
        node->value = read_byte(bs);
    } else {
        // Não é Folha: Chama recursivamente
        node->is_leaf = 0; 
        int half_size = size/2;

        node->children[0] = decode_quadtree(bs, total_width, start_x, start_y, half_size);
        node->children[1] = decode_quadtree(bs, total_width, start_x + half_size, start_y, half_size);
        node->children[2] = decode_quadtree(bs, total_width, start_x, start_y + half_size, half_size);
        node->children[3] = decode_quadtree(bs, total_width, start_x + half_size, start_y + half_size, half_size);
        
        // Nó pai não precisa de valor.
        node->value = 0; 
    }
    return node;
}

// Função principal de Descodificação PGM
void decode_pgm_image(char *input_qcf, char *output_pgm) {
    struct pgm img;
    QuadNode *root = NULL;
    
    BitStreamReader *bs = create_bitstream_reader(input_qcf);
    
    // 1. Lê o cabeçalho
    read_qcf_header(bs, &img);
    printf("DEBUG: Imagem alvo: %d x %d (Max Val: %d)\n", img.c, img.r, img.mv);
    
    // 2. Aloca a memória para os dados da imagem (descomprimida)
    img.pData = (unsigned char *)malloc(img.r * img.c * sizeof(unsigned char));
    if (!img.pData) exit(1);
    
    // 3. Descodifica a Quadtree
    root = decode_quadtree(bs, img.c, 0, 0, img.c);
    
    // 4. Reconstroi a matriz de pixels PGM usando a Quadtree
    reconstructPGMImage(root, img.pData, img.c);
    
    // 5. Salva a imagem PGM (Descomprimida)
    img.tipo = 5; // Formato P5
    writePGMImage(&img, output_pgm);
    
    printf("Descompressão concluída. Imagem PGM salva em: %s\n", output_pgm);
    
    // 6. Limpeza
    close_bitstream_reader(bs);
    free(img.pData);
    if (root) freeQuadtree(root);
}