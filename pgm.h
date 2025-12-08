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

#ifndef PGM_H
#define PGM_H

struct pgm {
    int tipo;
    int c; 
    int r; 
    int mv;
    unsigned char *pData;
};

void readPGMImage(struct pgm *, char *);
void writePGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);

#endif 