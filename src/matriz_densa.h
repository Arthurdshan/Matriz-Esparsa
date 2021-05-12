#pragma once

double **MD_Carregar(char *nome_do_arquivo, int *n, int *m);
void MD_MultiplicarMatrizVetor(double** M, int n, int m, double *v, double *resultado);
void MD_Imprimir(double **matriz, int n, int m);
void MD_Destruir(double **matriz, int n, int m);