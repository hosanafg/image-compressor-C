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

#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include "../bib/quadtree.h"
#include "../bib/pgm.h" 

typedef struct {
    FILE *fp;             
    unsigned char buffer; 
    int bit_count;        
    int is_loaded;        
} BitStreamReader;

BitStreamReader* create_bitstream_reader(char *filename);
int read_bit(BitStreamReader *bs);
unsigned char read_byte(BitStreamReader *bs);
void close_bitstream_reader(BitStreamReader *bs);

void read_qcf_header(BitStreamReader *bs, struct pgm *pio);
QuadNode* decode_quadtree(BitStreamReader *bs, int total_width, int start_x, int start_y, int size);
void decode_pgm_image(char *input_qcf, char *output_pgm);

#endif
