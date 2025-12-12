/* 
******************************************************

Aluna: Hosana Fernandes Gomes
Matrícula: 20251045050585
Aluno: Pedro Vasconcelos Almeida
Matrícula: 20251045050437
Aluno: Daniel Fernandes Monteiro da Silva
Matrícula: 20251045050534
Avaliação 04: Trabalho Final
04.505.23 − 2025.2 − Prof.Daniel Ferreira
Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
S.O: Windows 11

********************************************************
*/

#include "../bib/decoder.h"
#include <stdio.h>
#include <stdlib.h>

BitStreamReader* create_bitstream_reader(char *filename) {
    BitStreamReader *bs = malloc(sizeof(BitStreamReader));
    if (!bs) exit(1);

    bs->fp = fopen(filename, "rb");
    if (!bs->fp) {
        perror("Erro ao abrir arquivo compactado para leitura");
        free(bs);
        exit(1);
    }

    bs->buffer=0;
    bs->bit_count=0;
    bs->is_loaded=0; 
    return bs;
}

int read_bit(BitStreamReader *bs) {
    if (bs->bit_count == 0 && bs->is_loaded == 0) {
        if (fread(&(bs->buffer), sizeof(unsigned char), 1, bs->fp) != 1) {
            return -1;
        }
        bs->bit_count=8; 
        bs->is_loaded=1;
    } 
    else if (bs->bit_count==0 && bs->is_loaded==1) {
        if (fread(&(bs->buffer), sizeof(unsigned char), 1, bs->fp) != 1) {
            return -1; 
        } bs->bit_count=8;
    }

    int bit = (bs->buffer >> 7) & 1; 
    bs->buffer <<= 1;
    bs->bit_count--;

    return bit;
}

unsigned char read_byte(BitStreamReader *bs) {
    unsigned char value=0;
    for (int i=0; i<8; i++) {
        int bit=read_bit(bs);
        if (bit == -1) {
            fprintf(stderr, "Erro ao ler byte do bitstream: Fim inesperado do arquivo.\n");
            return 0;
        } value = (value << 1) | bit;
    } return value;
}

void read_bitstream_header(BitStreamReader *bs, struct pgm *pio) {
    fread(&(pio->c), sizeof(int), 1, bs->fp);
    fread(&(pio->r), sizeof(int), 1, bs->fp);
    fread(&(pio->mv), sizeof(int), 1, bs->fp);

    bs->buffer=0;
    bs->bit_count=0; 
    bs->is_loaded=0; 
}

void close_bitstream_reader(BitStreamReader *bs) {
    if (bs) {
        fclose(bs->fp);
        free(bs);
    }
}

QuadNode* decode_quadtree(BitStreamReader *bs, int total_width, int start_x, int start_y, int size) {
    
    int flag_bit=read_bit(bs);
    if (flag_bit==-1) return NULL; 
    
    QuadNode *node=malloc(sizeof(QuadNode));
    if (!node) exit(1);
    
    node->x=start_x;
    node->y=start_y;
    node->width=node->height = size;

    for (int i=0; i<4; i++) node->children[i] = NULL; 

    if (flag_bit==1) { 
        node->is_leaf=1; 
        node->value=read_byte(bs);
    } else {
        node->is_leaf=0; 
        int half_size=size/2;

        node->children[0] = decode_quadtree(bs, total_width, start_x, start_y, half_size);
        node->children[1] = decode_quadtree(bs, total_width, start_x + half_size, start_y, half_size);
        node->children[2] = decode_quadtree(bs, total_width, start_x, start_y + half_size, half_size);
        node->children[3] = decode_quadtree(bs, total_width, start_x + half_size, start_y + half_size, half_size);

        node->value = 0; 
    } return node;
}

void decode_pgm_image(char *input_bitstream, char *output_pgm) {
    struct pgm img;
    QuadNode *root=NULL;
    BitStreamReader *bs=create_bitstream_reader(input_bitstream);

    read_bitstream_header(bs, &img);
    printf("DEBUG: Imagem alvo: %d x %d (Max Val: %d)\n", img.c, img.r, img.mv);

    img.pData=malloc(img.r * img.c * sizeof(unsigned char));
    if (!img.pData) exit(1);

    root = decode_quadtree(bs, img.c, 0, 0, img.c);
    reconstructPGMImage(root, img.pData, img.c);
    img.tipo=5; 
    writePGMImage(&img, output_pgm);
    
    printf("Descompressão concluída. Imagem PGM salva em: %s\n", output_pgm);

    close_bitstream_reader(bs);
    free(img.pData);
    if (root) freeQuadtree(root);
}