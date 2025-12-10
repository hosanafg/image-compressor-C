/* 
******************************************************

Aluna: Hosana Fernandes Gomes
Matrícula: 20251045050585
Aluno: Mateus Oliveira Santos
Matrícula: 20251045050330
Avaliação 04: Trabalho Final
04.505.23 − 2025.2 − Prof.Daniel Ferreira
Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0
S.O: Windows 11

********************************************************
*/

#include "../bib/quadtree.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char get_pixel_value(unsigned char *pData, int total_width, int x, int y) {
    return pData[y * total_width + x];
}

unsigned char calculate_average (unsigned char *pData, int total_width, int start_x, 
                                int start_y, int size) {
    long sum = 0;
    for (int j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            sum += get_pixel_value(pData, total_width, start_x + i, start_y + j);
        }
    } return (unsigned char)(sum/(size * size));
}

int is_homogeneous_tolerant (unsigned char *pData, int total_width, int start_x, int start_y, 
                            int size, int threshold) {
    
    unsigned char avg_value = calculate_average(pData, total_width, start_x, start_y, size);

    for (int j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            unsigned char current_pixel = get_pixel_value(pData, total_width, start_x + i, start_y + j);
            if (abs(current_pixel - avg_value) >= threshold*1.3) return 0;
        }
    } return 1; 
}

QuadNode* build_quadtree (unsigned char *pData, int total_width, int start_x, int start_y, 
                          int size, int threshold) {

    QuadNode *node = (QuadNode *)malloc(sizeof(QuadNode));
    if (!node) exit(1);

    node->x = start_x;
    node->y = start_y;
    node->width = node->height = size;

    for (int i = 0; i < 4; i++) node->children[i] = NULL; 

    if (size == 1 || is_homogeneous_tolerant(pData, total_width, start_x, start_y, size, threshold)) {
        node->is_leaf = 1; 
        node->value = (char)(calculate_average(pData, total_width, start_x, start_y, size)-128);
        return node;
    } 

    node->is_leaf = 0; 
    int half_size = size/2;

    node->children[0] = build_quadtree(pData, total_width, start_x, start_y, half_size, threshold);
    node->children[1] = build_quadtree (pData, total_width, start_x + half_size, 
                                        start_y, half_size,threshold);
    node->children[2] = build_quadtree (pData, total_width, start_x, start_y + half_size, 
                                        half_size, threshold);
    node->children[3] = build_quadtree (pData, total_width, start_x + half_size, start_y + half_size, 
                                        half_size, threshold);

    return node;
}

void reconstructPGMImage(QuadNode *node, unsigned char *pData, int total_width) {
    if (node->is_leaf == 1) {
        for (int y=0; y<node->height; y++) {
            for (int x=0; x < node->width; x++) {
                int global_x = node->x + x;
                int global_y = node->y + y;
                pData[global_y * total_width + global_x] = (unsigned char)node->value+128;
            }
        }
    } else {
        for (int i=0; i<4; i++) {
            if (node->children[i] != NULL) {
                reconstructPGMImage(node->children[i], pData, total_width);
            }
        }
    }
}

void freeQuadtree(QuadNode *node) {
    if (node == NULL) return;
    for (int i=0; i<4; i++) {
        freeQuadtree(node->children[i]);
    } free(node);
}
