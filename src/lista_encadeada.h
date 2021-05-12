#pragma once 

typedef struct no {
    int chave;
    struct no *prox;
} No;

typedef struct lista {
    No *inicio;
    No *fim;
    int tam;
} Lista;

Lista *LE_Criar();
void LE_Inserir(Lista *lista, int chave);
int LE_Vazia(Lista *lista);
int LE_Tamanho(Lista *lista);
void LE_Destruir(Lista *lista);
void LE_Remover(Lista *lista, int chave);