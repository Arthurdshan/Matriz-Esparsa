#pragma once 

typedef enum ESTADO {
    E_LIVRE,
    E_OCUPADO,
    E_APAGADO
} ESTADO;

typedef struct ELEMENTO {
    int chave;
    double data;
    ESTADO estado;
} ELEMENTO;

typedef struct THEA {
    ELEMENTO *tabela;
    int m;  
    int n;  
} THEA;

THEA *THEA_Criar(int m);
int THEA_Hash(THEA *TH, int chave, int k);
int THEA_Inserir(THEA *TH, int chave, double valor);
int THEA_Buscar(THEA *TH, int chave);
void THEA_Remover(THEA *TH, int chave);
int *THEA_Chaves(THEA *TH);
int THEA_NumChaves(THEA *TH);