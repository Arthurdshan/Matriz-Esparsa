#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "vetor_esparso.h"
#include "lista_encadeada.h"

/* Tamanho inicial da tabela hash no vetor esparso */
#define TAM_INICIAL_HASH 3

/* Funções auxiliares */
static double AUX_ProdutoEscalar(VetorEsparso *v1, VetorEsparso *v2) {
    int i;
    double soma = 0;
    No *aux = v1->chaves->inicio;
    
    for(i = 0; i < LE_Tamanho(v1->chaves); i++) {
        soma += VE_Buscar(v1, aux->chave) * VE_Buscar(v2, aux->chave);
        aux = aux->prox;
    }
    return soma;
}

static VetorEsparso *AUX_MultiplicaVetor(VetorEsparso *v1, VetorEsparso *v2) {
    VetorEsparso *novo = VE_Criar(VE_Dimensao(v1));

    int i;
    double aux = 0;
    No *aux2 = v1->chaves->inicio; 
    
    for(i = 0; i < LE_Tamanho(v1->chaves); i++) {
        aux = VE_Buscar(v1, aux2->chave) * VE_Buscar(v2, aux2->chave); 
        VE_Atribuir(novo, aux2->chave, aux);
        aux2 = aux2->prox;
    }
    return novo;
}

static VetorEsparso *AUX_SomaVetor(VetorEsparso *v1, VetorEsparso *v2) {
    VetorEsparso *novo = VE_Criar(VE_Dimensao(v1));
    
    int i;
    double aux2 = 0;
    No *aux = v1->chaves->inicio;

    for(i = 0; i < LE_Tamanho(v1->chaves); i++) {
        aux2 = VE_Buscar(v1, aux->chave) + VE_Buscar(v2, aux->chave); 
        VE_Atribuir(novo, aux->chave, aux2);
        aux = aux->prox;
    }
    return novo;
}

/* IMPLEMENTAÇÕES */

/* Esta função deve alocar uma nova estrutura VetorEsparso e inicializá-la adequadamente. O parâmetro m
indica o número de colunas do vetor. m também é chamado de dimensão do vetor. */
VetorEsparso *VE_Criar(int m) {
    VetorEsparso *VE = (VetorEsparso *)malloc(sizeof(VetorEsparso));
    
    VE->chaves = LE_Criar();
    VE->data = THEA_Criar(TAM_INICIAL_HASH);
    VE->m = m;

    return VE;
}
/* Esta função retorna a dimensão do vetor v, ou seja, o número de colunas. */
int VE_Dimensao(VetorEsparso *v) {
    return v->m;
}

/* Esta função retorna a dimensão do vetor v, ou seja, o número de colunas. */
int VE_NNaoZeros(VetorEsparso *v) {
    return v->data->n;
}

/* Esta função atribui valor na coluna col do vetor esparso v. Note que, na prática, você deve verificar se a
chave col já está inserida na estrutura subjacente. Caso não esteja, o elemento deve ser inserido na estrutura
com o valor. Caso já esteja, o valor deve ser atualizado na estrutura. Caso o valor atribuído seja zero, a
chave deve ser removida da estrutura, uma vez que a idéia é que os elementos zero não sejam armazenados. */
void VE_Atribuir(VetorEsparso *v, int col, double valor) {
    assert(col >= 0 && col < VE_Dimensao(v));

    int pos = THEA_Buscar(v->data, col);

    if(valor == 0 && pos != -1) {
        THEA_Remover(v->data, col);
        LE_Remover(v->chaves, col);
    }
    else if(valor == 0 && pos == -1) 
        return;
    else if(valor != 0 && pos != -1)
        v->data->tabela[pos].data = valor;
    else {
        THEA_Inserir(v->data, col, valor);
        LE_Inserir(v->chaves, col);
    }
}

/* Esta função retorna o valor armazenado no vetor esparso v na coluna col. Lembre-se que os valores 0 não
precisam ser armazenados no vetor. Portanto, caso a chave col não esteja na estrutura, basta retornar 0. */
double VE_Buscar(VetorEsparso *v, int col) {
    assert(col >= 0 && col < VE_Dimensao(v));
    
    if(THEA_Buscar(v->data, col) == -1) 
        return 0;
    else 
        return v->data->tabela[THEA_Buscar(v->data, col)].data;
}

/* Esta função calcula o produto escalar entre os vetores v e u. Verifique a definição de algébrica de produto
escalar na wikipédia. */
double VE_ProdutoEscalar(VetorEsparso *v, VetorEsparso *u) {
    assert(VE_Dimensao(v) == VE_Dimensao(u));

    if(VE_NNaoZeros(v) <= VE_NNaoZeros(u)) 
        return AUX_ProdutoEscalar(v, u);    
    else
        return AUX_ProdutoEscalar(u, v);
}

/* Esta função multiplica cada elemento diferente de zero do vetor esparso v ao escalar alpha e armazena o
resultado de volta no vetor. Implemente esta função para que seja eficiente, de forma que acesse o mínimo
possível de posições com valor zero no vetor v. */
void VE_MultiplicaEscalar(VetorEsparso *v, double alpha) {
    if(v == NULL) return;

    No *aux = v->chaves->inicio;
    for(int i = 0; i < LE_Tamanho(v->chaves); i++) {
        v->data->tabela[aux->chave].data = VE_Buscar(v, aux->chave) * alpha;
        aux = aux->prox;
    }
}

/* Esta função retorna um novo vetor tal que cada posição é o produto dos elementos correspondentes nos
vetores esparsos u e v. Implemente esta função para que seja eficiente, de forma que acesse o mínimo possível
de posições zeradas em ambos vetores de entrada. */
VetorEsparso *VE_MultiplicaVetor(VetorEsparso *v, VetorEsparso *u) {
    assert(VE_Dimensao(v) == VE_Dimensao(u));

    if(VE_NNaoZeros(v) <= VE_NNaoZeros(u)) 
        return AUX_MultiplicaVetor(v, u);
    else 
        return AUX_MultiplicaVetor(u, v);
}

/* Esta função retorna um novo vetor tal que o valor de cada posição é a soma dos elementos correspondentes
nos vetores esparsos u e v. Implemente esta função para que seja eficiente, de forma que acesse o mínimo
possível de posições zeradas em ambos vetores de entrada. */
VetorEsparso *VE_SomaVetor(VetorEsparso *v, VetorEsparso *u) {
    assert(VE_Dimensao(v) == VE_Dimensao(u));

    if(VE_NNaoZeros(v) >= VE_NNaoZeros(u)) 
        return AUX_SomaVetor(v, u);
    else 
        return AUX_SomaVetor(u, v);
}

/* Esta função libera todos os recursos alocados dinamicamente para o vetor esparso v. */
void VE_Destruir(VetorEsparso *v) {
    LE_Destruir(v->chaves);
    free(v->data->tabela);
    free(v->data);
    free(v);
}

/* Esta função imprime o vetor em forma de tabela hash  */
void VE_imprimir(VetorEsparso *v) {
    if(v == NULL || v->m == 0 || v->data->m == 0) return;
    printf("colunas: %d, tamanho da TH: %d, elementos na TH: %d\n", v->m, v->data->m, v->chaves->tam);
    for(int i = 0; i < v->data->m; i++) {
        if(v->data->tabela[i].estado == E_OCUPADO) {
            printf("chave: %d\t", v->data->tabela[i].chave);
            printf("data: %lf\n", VE_Buscar(v, i));
        }
    }
    printf("\n");
}