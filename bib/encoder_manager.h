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

#ifndef ENCODER_MANAGER
#define ENCODER_MANAGER

#include <stdlib.h>
#include <stdio.h>
#include "../bib/quadtree.h"

void run_encode(char *input_pgm, char *output_bit, char *output_reconstructed_pgm, int threshold);
void apply_smoothing_filter(unsigned char *pData, int total_width, int total_height);

#endif
