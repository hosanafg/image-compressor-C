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

#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "../bib/quadtree.h" 

typedef struct {
    FILE *fp;             
    unsigned char buffer; 
    int bit_count;        
} BitStreamWriter;

BitStreamWriter* create_bitstream_writer(char *filename);
void write_bit(BitStreamWriter *bs, int bit);
void flush_bitstream(BitStreamWriter *bs);
void close_bitstream_writer(BitStreamWriter *bs);
void encode_quadtree(QuadNode *root, BitStreamWriter *bs);

#endif
