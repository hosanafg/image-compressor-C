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

#ifndef QUADTREE_H
#define QUADTREE_H

typedef struct QuadNode {
    char value; 
    int is_leaf;         
    int x, y, width, height; 
    struct QuadNode *children[4]; 
} QuadNode;

QuadNode* build_quadtree(unsigned char *pData, int total_width, int start_x, int start_y, 
                        int size, int threshold);

unsigned char get_pixel_value(unsigned char *pData, int total_width, int x, int y);
void reconstructPGMImage(QuadNode *node, unsigned char *pData, int total_width);
void apply_smoothing_filter(unsigned char *pData, int total_width, int total_height);
void freeQuadtree(QuadNode *node);

#endif 
