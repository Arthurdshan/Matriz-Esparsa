#include <stdlib.h>

#include "THEA.h"

static void THEA_redimensionar(THEA *TH, int novo_m) {
    ELEMENTO *novo, *antigo;
    int i, m_antigo;

    novo = (ELEMENTO *)malloc(sizeof(ELEMENTO) * novo_m);
    
    for(i = 0; i < novo_m; i++) novo[i].estado = E_LIVRE;

    antigo = TH->tabela;
    m_antigo = TH->m;

    TH->tabela = novo;
    TH->m = novo_m;
    TH->n = 0;

    for(int i = 0; i < m_antigo; i++) 
        if(antigo[i].estado == E_OCUPADO) 
            THEA_Inserir(TH, antigo[i].chave, antigo[i].data);
    
    free(antigo);
}

THEA *THEA_Criar(int m) {
    THEA *nova = (THEA *)malloc(sizeof(THEA));
    nova->tabela = (ELEMENTO *)malloc(sizeof(ELEMENTO) * m);

    nova->m = m;
    nova->n = 0;

    for(int i = 0; i < m; i++)
        nova->tabela[i].estado = E_LIVRE;

    return nova;
}

int THEA_Hash(THEA *TH, int chave, int k) {
    return ((chave % TH->m) + k) % TH->m;
}

int THEA_Inserir(THEA *TH, int chave, double valor) {
    int h, k, h_inicial;
    k = 0;

    if(TH->n > TH->m / 2)
        THEA_redimensionar(TH, TH->m * 2);
    
    h = THEA_Hash(TH, chave, k);
    h_inicial = h;
 
    while(TH->tabela[h].estado == E_OCUPADO) {
        if(TH->tabela[h].chave == chave) {
            TH->n--;
            break;
        }

        k++;
        h = THEA_Hash(TH, chave, k);
        
        if(h == h_inicial) return -1;
    }

    TH->n++;
    TH->tabela[h].chave = chave;
    TH->tabela[h].data = valor;
    TH->tabela[h].estado = E_OCUPADO;

    return h;
}

int THEA_Buscar(THEA *TH, int chave) { 
    int h, h_inicial, k;
    k = 0;
    h = THEA_Hash(TH, chave, k);
    h_inicial = h;

    while(TH->tabela[h].estado != E_LIVRE) {
        if((TH->tabela[h].estado == E_OCUPADO) && (TH->tabela[h].chave == chave))
            return h;
        
        k++;
        h = THEA_Hash(TH, chave, k);

        if(h_inicial == h) return -1;
    }
    return -1;
}

void THEA_Remover(THEA *TH, int chave) {
    int p = THEA_Buscar(TH, chave);
    if(p != -1) {
        TH->tabela[p].estado = E_APAGADO;
        TH->n--;
    }
}