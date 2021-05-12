#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "matriz_esparsa.h"
#include "matriz_densa.h"
#include "vetor_dinamico.h"
#include "testes_TAD.h"

/* Realiza os testes da matriz esparsa. Carrega do arquivo
e realiza a multiplicação */
void testes_matriz_esparsa(char *matriz, char *vetor) {
    clock_t t = 0;

    MatrizEsparsa *m = ME_Carregar(matriz);
    MatrizEsparsa *v = ME_Carregar(vetor);
    VetorEsparso *u;

    t = clock();
    u = ME_MultiplicaVetor(m, v->matriz[0]);
    t = clock() - t;

    printf("Tempo total: %f\n", ((float)t)/CLOCKS_PER_SEC);

    ME_Salvar(m, "matriz.txt");

    ME_Destruir(m); m = NULL;
    ME_Destruir(v); v = NULL;
    VE_Destruir(u); u = NULL;
}

/* Realiza os testes da matriz densa. Carrega do arquivo
e realiza a multiplicação */
void testes_matriz_densa(char *matriz, char *vetor) {
    clock_t t = 0;

    double **md1; // pointeiro para ponteiro (matriz)
    double **md2;
    
    int n1 = 0; // nº de linhas
    int m1 = 0; // nº de colunas
    
    int n2 = 0;
    int m2 = 0;

    md1 = MD_Carregar(matriz, &n1, &m1);
    md2 = MD_Carregar(vetor, &n2, &m2);

    double *resultado = VD_Criar(m2);

    t = clock();
    MD_MultiplicarMatrizVetor(md1, n1, m1, md2[0], resultado);
    t = clock() - t;
    
    printf("Tempo total: %f\n", ((float)t)/CLOCKS_PER_SEC);

    MD_Destruir(md1, n1, m1); md1 = NULL;
    MD_Destruir(md2, n2, m2); md2 = NULL;
    VD_Destruir(resultado); resultado = NULL;
}

void matriz_esparsa() {
    printf("TESTES NA MATRIZ ESPARSA\n\n");
    printf("Esparsidade do vetor: 0.95\n\n");

    testes_matriz_esparsa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.95-s.txt"); 
    testes_matriz_esparsa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    
    printf("\nEsparsidade do vetor: 0.75\n\n");

    testes_matriz_esparsa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    
    printf("\nEsparsidade do vetor: 0.55\n\n");
    
    testes_matriz_esparsa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    
    printf("\nEsparsidade do vetor: 0.35\n\n");

    testes_matriz_esparsa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    
    printf("\nEsparsidade do vetor: 0.15\n\n");

    testes_matriz_esparsa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    
    printf("\nEsparsidade do vetor: 0.05\n\n");

    testes_matriz_esparsa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
    testes_matriz_esparsa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
}

void matriz_densa() {
    printf("\n\nTESTES NA MATRIZ DENSA\n\n");    
    printf("\nEsparsidade do vetor: 0.95\n\n");
        
    testes_matriz_densa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.95-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.95-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.95-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.95-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.95-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.95-s.txt");
    
    printf("\nEsparsidade do vetor: 0.75\n\n");

    testes_matriz_densa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.75-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.75-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.75-s.txt");
    
    printf("\nEsparsidade do vetor: 0.55\n\n");
        
    testes_matriz_densa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.55-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.55-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.55-s.txt");
    
    printf("\nEsparsidade do vetor: 0.35\n\n");
        
    testes_matriz_densa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.35-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.35-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.35-s.txt");
    
    printf("\nEsparsidade do vetor: 0.15\n\n");

    testes_matriz_densa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.15-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.15-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.15-s.txt");
    
    printf("\nEsparsidade do vetor: 0.05\n\n");

    testes_matriz_densa("testes/M_10-n_10-m_0.95-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.85-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.75-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_densa("testes/M_10-n_10-m_0.65-s.txt", "testes/V_1-n_10-m_0.05-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.95-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.85-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.75-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_densa("testes/M_100-n_100-m_0.65-s.txt", "testes/V_1-n_100-m_0.05-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.95-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.85-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.75-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
    testes_matriz_densa("testes/M_1000-n_1000-m_0.65-s.txt", "testes/V_1-n_1000-m_0.05-s.txt");
}

void executar_testes() { 
    matriz_esparsa(); 
    matriz_densa(); 
}