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

#ifndef COMPRESSIONFACTOR_H
#define COMPRESSIONFACTOR_H

#include <string.h>
#include <stdio.h>

typedef enum {
    error=0, baixo,medio,alto, altissimo,
} fatorCompressao;

fatorCompressao imgQuality (const char *str);
int getThreshold(const char *str);

#endif
