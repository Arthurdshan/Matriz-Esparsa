/* Implementação auxiliar para os testes da matriz densa */

#include <stdlib.h>

#include "vetor_dinamico.h"

double *VD_Criar(int m) {
    double *v = (double *)calloc(m, sizeof(double));
    
    return v;
}

void VD_Destruir(double *v) {
    free(v);
}