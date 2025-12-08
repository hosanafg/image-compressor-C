#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define TAM_MAX 10

typedef struct {
    int c;
    int r;
    int *pData;
} Matrix;

int getSize (const char *msg) {
    int size;
    puts(msg);

    while (scanf("%d",&size)!=1 || size<=0) {
        puts("Erro! O tamanho deve ser maior que zero. ");
        scanf("%d",&size);
    }
    return size;
}

void createMatrix (Matrix *list, const int size) {
    list->c=size;
    list->r=size;
    list->pData=malloc((list->c)*(list->r)*sizeof(int));

    if(list->pData == NULL) {
        puts("Erro na alocação de memória! ");
        exit(1);
    }
}

void populateMatrix (Matrix *list) {
    for (int i=0;i< (list->r);i++) {
        for (int j=0; j<(list->c); j++) {
            list->pData[i*(list->c)+j]=rand() % TAM_MAX;
        }
    }
}

void printMatrix (Matrix *list) {
    for (int i=0; i<(list->r); i++) {
        for (int j=0; j<(list->c); j++) {
            printf("%2d ", list->pData[i*(list->c)+j]); 
        } printf("\n");
    } 
}

int checkSymmetry (Matrix *list) {
    if (list->r != list->c) {
        printf("A matriz não é quadrada. Não pode ser simétrica.\n");
        return 0;
    }
    for (int i=0;i<(list->r); i++) {
        for (int j=0; j< (list->c); j++) {
            if(list->pData[i*(list->c)+j]!=list->pData[j*(list->c)+i]){
                return 0;   
            }
        }
    } 
    return 1;
}

void printSymmetryResult(const Matrix *list) {
    int is_symmetric = checkSymmetry(list);
    if (is_symmetric == 1) printf("\nA matriz É simétrica!\n");
    else if (is_symmetric == 0) printf("\nA matriz NÃO é simétrica.\n");
}

int interpolateMatrixElement(Matrix *list, int row, int col) {
    if (row<0 || row>=list->r || col<0 || col>=list->c) {
        printf("Erro: Coordenadas (%d, %d) fora dos limites da matriz.\n", row, col);
        return 0;
    }

    long long sum_neighbors = 0;
    int count_neighbors = 0;

    for (int i=row-1; i<=row+1; i++) {
        for (int j=col-1; j<=col+1; j++) {
            if (i<0 || i >= list->r || j<0 || j>= list->c) continue;
            if (i==row && j==col) continue;
            int index = i *(list->c)+ j;
            sum_neighbors += list->pData[index];
            count_neighbors++;
        }
    }

    if (count_neighbors>0) {
        int index_target = row*(list->c)+col;
        list->pData[index_target] = (int)(sum_neighbors/count_neighbors);
        return 1;
    }
    return 0; 
}

int main() {
    Matrix matriz;
    srand(time(NULL));
    int tamanho = getSize("Digite o tamanho da matriz quadrada:  ");

    createMatrix (&matriz, tamanho);
    populateMatrix(&matriz);

    int posicaoColuna=rand()%matriz.c;
    int posicaoLinha=rand()%matriz.r;

    puts("Antes de interpolar: ");
    printMatrix(&matriz);
    checkSymmetry(&matriz);
    printSymmetryResult(&matriz);
    
    interpolateMatrixElement(&matriz,posicaoLinha,posicaoColuna);
    puts("Após interpolar:");
    printf("Elemento (%d,%d)\n",posicaoLinha,posicaoColuna);
    printMatrix(&matriz);
    
    return 0;
}