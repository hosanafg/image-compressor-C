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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bib/pgm.h"     
#include "../bib/quadtree.h"
#include "../bib/encoder.h"
#include "../bib/decoder.h"
#include "../bib/compressionfactor.h"
#include "../bib/encoder_manager.h"

int main(int argc, char *argv[]) {
    int thresholdTeste = 0; 

    if (argc < 4) {
        printf("Uso:\n");
        printf("  Compressão: %s encode <entrada.pgm> <saida.qcf> <reconstruida.pgm> <fator de compressao: altissimo, alto, medio ou baixo> \n", argv[0]);
        printf("  Descompressão: %s decode <entrada.qcf> <saida.pgm>\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "encode") == 0) {
        if (argc != 6) { 
            printf("Erro: Formato incorreto para o modo 'encode'.\n");
            printf("Uso: %s encode <entrada.pgm> <saida.qcf> <reconstruida.pgm> <fator de compressao: alto, medio, baixo>\n", argv[0]);
            exit(1);
        } 
    
    thresholdTeste=getThreshold(argv[5]);
    run_encode(argv[2], argv[3], argv[4], thresholdTeste);
        
    } else if (strcmp(argv[1], "decode") == 0) {
        if (argc != 4) { 
            printf("Erro: Formato incorreto para o modo 'decode'.\n");
            printf("Uso: %s decode <entrada.qcf> <saida.pgm>\n", argv[0]);
            exit(1);
        } decode_pgm_image(argv[2], argv[3]);
        
    } else {
        printf("Erro: Modo '%s' não reconhecido. Use 'encode' ou 'decode'.\n", argv[1]);
        exit(1);
    }

    return 0;
}
