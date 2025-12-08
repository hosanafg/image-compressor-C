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

#include "encoder.h"
#include <stdio.h>
#include <stdlib.h>

BitStreamWriter* create_bitstream_writer (char *filename) {
    BitStreamWriter *bs = (BitStreamWriter *)malloc(sizeof(BitStreamWriter));
    if (!bs) exit(1);

    bs->fp = fopen(filename, "wb");
    if (!bs->fp) {
        perror("Erro ao abrir arquivo para escrita do bitstream");
        free(bs);
        exit(1);
    }

    bs->buffer = 0;
    bs->bit_count = 0;
    return bs;
}

void write_bit (BitStreamWriter *bs, int bit) {
    bs->buffer <<= 1; 
    if (bit) bs->buffer |= 1; 
    bs->bit_count++;

    if (bs->bit_count == 8) {
        fwrite(&(bs->buffer), sizeof(unsigned char), 1, bs->fp);
        bs->buffer = 0;
        bs->bit_count = 0;
    }
}

void flush_bitstream(BitStreamWriter *bs) {
    if (bs->bit_count > 0) {
        bs->buffer <<= (8 - bs->bit_count); 
        fwrite(&(bs->buffer), sizeof(unsigned char), 1, bs->fp);
        bs->buffer = 0;
        bs->bit_count = 0;
    }
}

void close_bitstream_writer(BitStreamWriter *bs) {
    if (bs) {
        fclose(bs->fp);
        free(bs);
    }
}

void write_byte(BitStreamWriter *bs, unsigned char value) {
    for (int i = 7; i >= 0; i--) {
        int bit = (value >> i) & 1;
        write_bit(bs, bit);
    }
}

void encode_quadtree(QuadNode *node, BitStreamWriter *bs) {
    if (node == NULL) return;

    if (node->is_leaf) {
        write_bit(bs, 1);
        write_byte(bs, node->value);
    } else {
        write_bit(bs, 0);
        for (int i = 0; i < 4; i++) {
            encode_quadtree(node->children[i], bs);
        }
    }
}