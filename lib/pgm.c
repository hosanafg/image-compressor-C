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
#include "../bib/pgm.h"

void readPGMImage(struct pgm *pio, char *filename) {

    FILE *fp=fopen(filename,"rb");
    char ch;

    if (fp == NULL) {
        perror("ERRO READ: Nao foi possivel abrir o arquivo.");
        fflush(stdout);
        exit(1);
    }
    //PRINT DEBUG: printf("DEBUG: Arquivo %s aberto com sucesso.\n", filename);

    if ((ch = getc(fp)) != 'P') {
        puts("A imagem fornecida não está no formato pgm");
        fflush(stdout);
        exit(2);
    }

    //print DEBUG printf("DEBUG: Tipo de PGM lido: P%d\n", pio->tipo);

    pio->tipo = getc(fp) - 48;
    fseek(fp, 1, SEEK_CUR);

    while ((ch = getc(fp)) == '#') {
        while ((ch = getc(fp)) != '\n');
    }

    fseek(fp, -1, SEEK_CUR);
    fscanf(fp, "%d %d", &pio->c, &pio->r);
    
    if (ferror(fp)) {
        perror(NULL);
        fflush(stdout);
        exit(3);
    }
    
    fscanf(fp, "%d", &pio->mv);
    fseek(fp, 1, SEEK_CUR);
    //print debug printf("DEBUG: Dimensoes lidas: %dx%d\n", pio->c, pio->r);

    pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));
    switch (pio->tipo) {

    case 2:
        puts("Lendo imagem PGM (dados em texto)");
        for (int i=0; i< (pio->r * pio->c); i++) {
            fscanf(fp, "%hhu", pio->pData + i);
        }  break;
    
    case 5:
        puts("Lendo imagem PGM (dados em binário)");
        fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
        break;
    
    default:
        puts("Não está implementado");
    }
    
    fclose(fp);
    puts("Leitura concluída com sucesso."); 
    fflush(stdout);
}

void writePGMImage(struct pgm *pio, char *filename) {
    
    FILE *fp;
    char ch;

    if (!(fp = fopen(filename, "wb"))) {
        perror("Erro.");
        exit(1);
    }

    fprintf(fp, "%s\n", "P5");
    fprintf(fp, "%d %d\n", pio->c, pio->r);
    fprintf(fp, "%d\n", 255);
    fwrite(pio->pData, sizeof(unsigned char), pio->c * pio->r, fp);   
    //print debug printf("DEBUG: Arquivo PGM de saída '%s' escrito com sucesso.\n", filename);
    
    fclose(fp);
}

void viewPGMImage(struct pgm *pio) {
    
    printf("Tipo: %d\n", pio->tipo);
    printf("Dimensões: [%d %d]\n", pio->c, pio->r);
    printf("Max: %d\n", pio->mv);

    for (int i=0; i<(pio->r * pio->c); i++) {
        if (!(i % pio->c))
            printf("\n");
        printf("%2hhu ", *(pio->pData + i));
    } printf("\n");
}

void exportPGMBinaryDataToText(struct pgm *pio, char *filename) {
    
    FILE *fp;
    if (!(fp = fopen(filename, "w"))) {
        perror("Erro ao abrir arquivo de exportação de texto.");
        exit(1);
    }

    for (int i=0; i < (pio->r * pio->c); i++) {
        fprintf(fp, "%hhu ", *(pio->pData + i));
        if ((i + 1) % pio->c == 0) {
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
    puts("\nDados binários da imagem exportados com sucesso para o arquivo de texto."); 
    fflush(stdout);
}
