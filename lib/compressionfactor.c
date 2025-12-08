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

#include "compressionfactor.h"
#include <stdio.h>
#include <stdlib.h>

fatorCompressao imgQuality (const char *str) {
    if(strcasecmp(str, "baixo")==0) return baixo;
    else if(strcasecmp(str,"medio")==0) return medio;
    else if(strcasecmp(str,"alto")==0) return alto;
    else if(strcasecmp(str,"altissimo")==0) return altissimo;
    else return error;
}

int getThreshold(const char *str) {
    fatorCompressao factor = imgQuality(str);
    int thresholdTemp=0;

    switch(factor){
        case altissimo:
            puts("Fator de compressão ALTISSIMO (acima de 50): imagem com muitas perdas!\n");
            thresholdTemp=80;
            break;

        case alto:
            puts("Fator de compressão ALTO (entre 25 e 50): imagem menor com mais perdas!\n");
            thresholdTemp=25;
            break;

        case medio:
            puts("Fator de compressão MEDIO (entre 10 e 25): imagem um pouco menor com menos perdas!\n");
            thresholdTemp=12;
            break;
        
        case baixo:
            puts("Fator de compressão BAIXO (abaixo de 10): imagem com menos redução de tamanho e melhor qualidade!\n");
            thresholdTemp=9;
            break;
        
        case error:
        default:
            puts ("Não é possível comprimir a imagem.");
            exit(1);
    } 
    
    return thresholdTemp;
}
