#pragma once

#include "THEA.h"
#include "lista_encadeada.h"

typedef struct VetorEsparso {
    int m; // numero de colunas
    THEA *data; // ponteiro para tabela hash 
    Lista *chaves; // lista encadeada contendo as chaves ocupadas 
} VetorEsparso;

VetorEsparso *VE_Criar(int m);
int VE_Dimensao(VetorEsparso *v);
int VE_NNaoZeros(VetorEsparso *v);
void VE_Atribuir(VetorEsparso *v, int col, double valor);
double VE_Buscar(VetorEsparso *v, int col);
double VE_ProdutoEscalar(VetorEsparso *v, VetorEsparso *u);
void VE_MultiplicaEscalar(VetorEsparso *v, double alpha);
VetorEsparso *VE_MultiplicaVetor(VetorEsparso *v, VetorEsparso *u);
VetorEsparso *VE_SomaVetor(VetorEsparso *v, VetorEsparso *u);
void VE_Destruir(VetorEsparso *v);
void VE_imprimir(VetorEsparso *v);