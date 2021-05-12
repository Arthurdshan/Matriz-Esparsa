#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "matriz_esparsa.h"

/* Esta função deve alocar uma nova estrutura MatrizEsparsa e inicializá-la adequadamente. O parâmetro n
indica o número de linhas da matriz, e m indica o número de colunas. */
MatrizEsparsa *ME_Criar(int n, int m) {
    MatrizEsparsa *novo = (MatrizEsparsa *)malloc(sizeof(MatrizEsparsa));
    novo->matriz = (VetorEsparso **)malloc(sizeof(VetorEsparso *) * n);
    
    novo->n = n;
    novo->m = m;
    
    for(int i = 0; i < n; i++)
        novo->matriz[i] = VE_Criar(m);
    
    return novo;
}

/* Esta função deve retornar o número de linhas da matriz M. */
int ME_NLinhas(MatrizEsparsa *M) {
    if(M == NULL) return 0;

    return M->n;
}

/* Esta função deve retornar o número de colunas da matriz M. */
int ME_MColunas(MatrizEsparsa *M) {
    if(M == NULL) return 0;
    
    return M->m;
}

/* Esta função atribui valor na linha lin, coluna col da matriz esparsa M. Na prática, o VetorEsparso correspondente a 
a linha lin deve ser obtido por acesso direto ao arranjo das linhas. Depois, basta invocar a função
VE_Atribuir para atualizar o vetor esparso adequadamente */
void ME_Atribuir(MatrizEsparsa *M, int lin, int col, double valor) {
    if(M == NULL) return;

    assert(lin >= 0 && lin < ME_NLinhas(M));
    assert(col >= 0 && lin < ME_MColunas(M));

    VE_Atribuir(ME_ObterLinha(M, lin), col, valor);
}

/*Esta função retorna o valor armazenado na linha lin, coluna col da matriz esparsa M. Na prática, o
VetorEsparso correspondenta a linha lin deve ser obtido por acesso direto ao arranjo das linhas. Depois,
basta invocar a função VE_Buscar para pesquisar o valor da coluna col. Um exemplo (incompleto) da
implementação dessa função está descrita no início deste texto. */
double ME_Buscar(MatrizEsparsa *M, int lin, int col) {
    if(M == NULL) return 0;

    assert(lin >= 0 && lin < ME_NLinhas(M));
    assert(col >= 0 && lin < ME_MColunas(M));
    
    return VE_Buscar(ME_ObterLinha(M, lin), col);
}

/* Esta função retorna o valor armazenado na linha lin, coluna col da matriz esparsa M. Na prática, o
VetorEsparso correspondenta a linha lin deve ser obtido por acesso direto ao arranjo das linhas. Depois,
basta invocar a função VE_Buscar para pesquisar o valor da coluna col. Um exemplo (incompleto) da
implementação dessa função está descrita no início deste texto. */
VetorEsparso *ME_ObterLinha(MatrizEsparsa *M, int lin) {
    if(M == NULL) return NULL;

    assert(lin >= 0 && lin < ME_NLinhas(M));

    return M->matriz[lin];
}

/* Esta função multiplica cada elemento diferente de zero da matriz esparsa M ao escalar alpha e armazena o
resultado de volta em M. */
void ME_MultiplicaEscalar(MatrizEsparsa *M, double alpha) {
    if(M == NULL) return;

    for(int i = 0; i < ME_NLinhas(M); i++)
        VE_MultiplicaEscalar(ME_ObterLinha(M, i), alpha);
}

/* Esta função calcula a multiplicação da matriz M pelo vetor v. O resultado desta operação é um novo vetor,
cuja i-ésima posição é o produto escalar entre a i-ésima linha de M e o vetor v. */
VetorEsparso *ME_MultiplicaVetor(MatrizEsparsa *M, VetorEsparso *v) {
    if(M == NULL || v == NULL) return NULL;

    assert(ME_MColunas(M) == VE_Dimensao(v));

    VetorEsparso *u = VE_Criar(ME_NLinhas(M));

    for(int i = 0; i < VE_Dimensao(u); i++) 
        VE_Atribuir(u, i, VE_ProdutoEscalar(ME_ObterLinha(M, i), v));

    return u;
}

/* Esta função retorna uma nova matriz tal que o valor de cada posição é a soma dos elementos correspondentes
das matrizes esparsas M e A. Implemente esta função para que seja eficiente, de forma que acesse o mínimo
possível de posições zeradas em ambas as matrizes de entrada. */
MatrizEsparsa *ME_SomaMatriz(MatrizEsparsa *M, MatrizEsparsa *A) {
    if(M == NULL || A == NULL) return NULL;

    assert(ME_NLinhas(M) == ME_MColunas(M));
    assert(ME_NLinhas(A) == ME_MColunas(A));

    MatrizEsparsa *ME = ME_Criar(ME_NLinhas(M), ME_MColunas(M));

    for(int i = 0; i < ME_NLinhas(M); i++) 
        for(int j = 0; j < ME_MColunas(M); j++) 
            ME_Atribuir(ME, i, j, ME_Buscar(M, i, j) + ME_Buscar(A, i, j));
    
    return ME;
}

/* Esta função carrega uma matriz de um arquivo salvo em nome_do_arquivo em uma MatrizEsparsa. O
arquivo tem o seguinte formato:
n
m
nnz
linha;coluna;valor
linha;coluna;valor
....
linha;coluna;valor
Onde n é o número de linhas, m é o número de colunas, nnz é o número de elementos diferentes de zero. Após
a linha nnz, há nnz linhas, cada uma no formato “linha;coluna;valor”, descrevendo cada um dos elementos
diferentes de zero da matriz. linha é um inteiro entre 0 e n − 1, coluna é um inteiro entre 0 e m − 1 e valor
é um número real, que deve ser lido para um double antes de ser colocado na matriz. */
MatrizEsparsa *ME_Carregar(char *nome_do_arquivo) {
    int n, m, nnz;
    double data;

    FILE *matriz = fopen(nome_do_arquivo, "r");    
    if(matriz == NULL) exit(0);

    fscanf(matriz, "%d", &n);
    fscanf(matriz, "%d", &m);
    fscanf(matriz, "%d", &nnz);

    MatrizEsparsa *me = ME_Criar(n, m);

    for(int i = 0; i < nnz; i++) {
        fscanf(matriz, "%d;%d;%lf", &n, &m, &data);
        ME_Atribuir(me, n, m, data);
    }
    
    fclose(matriz);

    return me;
}

/* Esta função salva a matriz esparsa M no arquivo nome_do_arquivo no formato descrito na função ME_Carregar */
void ME_Salvar(MatrizEsparsa* M, char *nome_do_arquivo) {
    if(M == NULL) return;

    FILE *matriz = fopen(nome_do_arquivo, "w+");
    if(matriz == NULL) exit(0);

    fprintf(matriz, "%d\n", ME_NLinhas(M));
    fprintf(matriz, "%d\n", ME_MColunas(M));
    
    int nnz = 0;
    
    for(int i = 0; i < ME_NLinhas(M); i++)
        nnz += VE_NNaoZeros(ME_ObterLinha(M, i));

    fprintf(matriz, "%d\n", nnz);
    
    for(int i = 0; i < ME_NLinhas(M); i++) {
        if(VE_NNaoZeros(ME_ObterLinha(M, i)) == 0) continue; // não possui elementos na linha
        
        No *aux = M->matriz[i]->chaves->inicio;
        for(int j = 0; j < LE_Tamanho(M->matriz[i]->chaves); j++) {
            fprintf(matriz, "%d;", i);
            fprintf(matriz, "%d;", aux->chave);
            fprintf(matriz, "%.3lf\n", ME_Buscar(M, i, aux->chave));
            aux = aux->prox;
        }
    }
    fclose(matriz);
}

/* Esta função salva a matriz esparsa M no arquivo nome_do_arquivo no formato descrito na função ME_Carregar */
void ME_Destruir(MatrizEsparsa *M) {
    if(M == NULL) return;

    for(int i = 0; i < ME_NLinhas(M); i++) {
        VE_Destruir(ME_ObterLinha(M, i));
    }
    free(M); M->matriz = NULL; M = NULL;
}

void ME_imprimir(MatrizEsparsa *M) {
    if(M == NULL) return;

    for(int i = 0; i < ME_NLinhas(M); i++) {
        for(int j = 0; j < ME_MColunas(M); j++) {
            printf("%.3lf\t", ME_Buscar(M, i, j));
        }
        printf("\n\n");
    }
    printf("\n");
} 