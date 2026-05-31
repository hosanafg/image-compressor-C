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

#include "../bib/compressionfactor.h"
#include <stdio.h>
#include <stdlib.h>

fatorCompressao imgQuality (const char *str) {
    if(strcasecmp(str, "baixo")==0) return baixo;
    else if(strcasecmp(str,"medio")==0) return medio;
    else if(strcasecmp(str,"alto")==0) return alto;
    else return error;
}

int getThreshold(const char *str) {
    fatorCompressao factor = imgQuality(str);
    float thresholdTemp=0;

    switch(factor){

        case alto:
            puts("Fator de compressão ALTO (acima de 25): imagem menor com mais perdas!\n");
            thresholdTemp=30;
            break;

        case medio:
            puts("Fator de compressão MEDIO (entre 10 e 25): imagem um pouco menor com menos perdas!\n");
            thresholdTemp=15;
            break;
        
        case baixo:
            puts("Fator de compressão BAIXO (abaixo de 10): imagem com menos redução de tamanho e melhor qualidade!\n");
            thresholdTemp=8;
            break;
        
        case error:
        default:
            puts ("Não é possível comprimir a imagem.");
            exit(1);
    } 
    
    return thresholdTemp;
}
