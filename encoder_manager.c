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

#include "encoder_manager.h" 
#include "pgm.h"           
#include "quadtree.h"      
#include "encoder.h"       
#include <stdio.h>         
#include <stdlib.h>        

void run_encode(char *input_pgm, char *output_qcf, char *output_reconstructed_pgm, int threshold) {
    struct pgm img;
    QuadNode *root = NULL;

    readPGMImage(&img, input_pgm);
    
    if (img.c != img.r || (img.c & (img.c - 1)) != 0) {
        printf("ERRO!: A imagem precisa ser quadrada e com dimensão potência de 2.\n");
        exit(1);
    }

    root = build_quadtree(img.pData, img.c, 0, 0, img.c, threshold);
    BitStreamWriter *bs = create_bitstream_writer(output_qcf);

    fwrite(&(img.c), sizeof(int), 1, bs->fp);
    fwrite(&(img.r), sizeof(int), 1, bs->fp);
    fwrite(&(img.mv), sizeof(int), 1, bs->fp);
    
    encode_quadtree(root, bs);
    flush_bitstream(bs);
    close_bitstream_writer(bs);

    reconstructPGMImage(root, img.pData, img.c);
    apply_smoothing_filter(img.pData, img.c, img.r);
    writePGMImage(&img, output_reconstructed_pgm);

    printf("Imagem PGM reconstruída salva como: %s\n", output_reconstructed_pgm);

    if (img.pData != NULL) free(img.pData);
    if (root != NULL) freeQuadtree(root);
}

//teste: filtro besta de suavizacao -> vamos tentar preservar a text. do tijilo 
void apply_smoothing_filter(unsigned char *pData, int total_width, int total_height) {
    unsigned char *temp_data = (unsigned char *)malloc(total_width * total_height * sizeof(unsigned char));
    if (!temp_data) {
        perror("Erro de alocacao para o buffer temporario.");
        return; 
    }
    for (int i = 0; i < total_width * total_height; i++) {
        temp_data[i] = pData[i];
    }
    for (int y = 1; y < total_height - 1; y++) {
        for (int x = 1; x < total_width - 1; x++) {
            long sum = 0;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    sum += get_pixel_value(pData, total_width, x + i, y + j);
                }
            } int index = y * total_width + x;
            temp_data[index] = (unsigned char)(sum / 9);
        }
    } for (int y = 1; y < total_height - 1; y++) {
        for (int x = 1; x < total_width - 1; x++) {
             int index = y * total_width + x;
             pData[index] = temp_data[index];
        }
    } free(temp_data);
}
