/* Implementação auxiliar para os testes da matriz densa */

#include <stdio.h>
#include <stdlib.h>

#include "matriz_densa.h"

double **MD_Carregar(char *nome_do_arquivo, int *n, int *m) {
    FILE *matriz = fopen(nome_do_arquivo, "r");
    if(matriz == NULL) exit(0);

    int nnz;

    fscanf(matriz, "%d", n);
    fscanf(matriz, "%d", m);
    fscanf(matriz, "%d", &nnz);

    double **densa = (double **)malloc(sizeof(double *) * *n);

    for(int i = 0; i < *n; i++) 
        densa[i] = (double *)calloc(*m, sizeof(double));

    int lin, col;
    
    double data;

    for(int i = 0; i < nnz; i++) {
        fscanf(matriz, "%d;%d;%lf", &lin, &col, &data);
        densa[lin][col] = data;
    }
    fclose(matriz);

    return densa;
}

void MD_MultiplicarMatrizVetor(double **M, int n, int m, double *v, double *resultado) {
    double aux = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            aux += M[i][j] * v[j];
        }
        resultado[i] = aux;
    }
}

void MD_Imprimir(double **matriz, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%.3lf\t", matriz[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");
}

void MD_Destruir(double **matriz, int n, int m) {
    for(int i = 0; i < n; i++) 
        free(matriz[i]);
    free(matriz);
}