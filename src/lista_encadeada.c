/* Implementação de uma lista encadeada para armazenar
as chaves dos vetores esparsos */
#include <stdlib.h>

#include "lista_encadeada.h"

/* Aloca dinamicamente uma lista vazia */
Lista *LE_Criar() {
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->inicio = NULL;
    novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

/* Insere um elemento na lista */
void LE_Inserir(Lista *lista, int chave) {
    if (lista == NULL) return;

    No *novo = (No *)malloc(sizeof(No));
    novo->prox = NULL;
    novo->chave = chave;

    if(LE_Vazia(lista)) {
        lista->inicio = novo;
        lista->fim = novo;
    }
    else {
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    lista->tam++;
}

/* Retorna 0 caso esteja com pelo menos 1 elemento, e 1 caso vazia */
int LE_Vazia(Lista *lista) {
    return lista->tam ? 0 : 1;
}

/* Retorna o tamanho da lista encadeada */
int LE_Tamanho(Lista *lista) {
    return lista->tam;
}

/* desaloca toda memória utilizada pela lista */
void LE_Destruir(Lista *lista) {
    No *aux;

    while(lista->inicio != NULL) {
        aux = lista->inicio;
        lista->inicio = lista->inicio->prox;
        free(aux);
    }
    lista->inicio = NULL;
    lista->fim = NULL;
    lista = NULL;
}

/* remove um nó da lista pela chave que foi passada */
void LE_Remover(Lista *lista, int chave) {
    if(lista == NULL) return;

    No *aux = lista->inicio;

    if(lista->inicio->chave == chave) {
        lista->inicio = lista->inicio->prox;
        free(aux);
        return;
    }

    No *aux2;

    while(aux->chave != chave) {
        aux2 = aux;
        aux = aux->prox;    
    }

    if(aux == NULL) return;

    aux2->prox = aux->prox;
    free(aux);
}