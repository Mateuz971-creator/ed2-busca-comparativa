#include <stdlib.h>
#include "hash.h"
#include "medicao.h"

/* Estrutura do nó para o encadeamento (lista ligada) */
typedef struct NoHash {
    int matricula;
    int pos;          // Posição do aluno no vetor original
    struct NoHash *prox;
} NoHash;

/* Estrutura da Tabela Hash (compatível com os campos n e m do main.c) */
struct Hash {
    int m;            // Tamanho da tabela (número primo)
    int n;            // Número de chaves inseridas
    NoHash **vetor;   // Vetor de ponteiros para as listas encadeadas
};

/* Cria a tabela hash com m listas */
Hash *hash_cria(int m) {
    Hash *h = malloc(sizeof(Hash));
    if (h == NULL) return NULL;
    h->m = m;
    h->n = 0;
    h->vetor = calloc((size_t)m, sizeof(NoHash *)); // Inicializa os ponteiros com NULL
    if (h->vetor == NULL) {
        free(h);
        return NULL;
    }
    return h;
}

/* Função hash utilizando o método da divisão: chave % m */
static int hash_funcao(int chave, int m) {
    int r = chave % m;
    return r < 0 ? r + m : r; // Garante que o índice seja positivo
}

/* Insere a matrícula e a posição no INÍCIO da lista encadeada */
void hash_insere(Hash *h, int matricula, int pos) {
    int idx = hash_funcao(matricula, h->m);

    NoHash *novo = malloc(sizeof(NoHash));
    if (novo == NULL) return;

    novo->matricula = matricula;
    novo->pos = pos;
    novo->prox = h->vetor[idx]; // O novo aponta para o antigo início da lista
    h->vetor[idx] = novo;       // O início da lista passa a ser o novo nó

    h->n++;
}

/* Busca a matrícula na tabela hash. 
   Regra de contagem: soma 1 a cada nó visitado na lista encadeada. */
int hash_busca(Hash *h, int matricula) {
    int idx = hash_funcao(matricula, h->m);
    NoHash *atual = h->vetor[idx];

    while (atual != NULL) {
        comparacoes++; // Conta cada nó visitado na lista ligada
        if (atual->matricula == matricula) {
            return atual->pos; // Retorna a posição do aluno no vetor
        }
        atual = atual->prox;
    }

    return -1; // Não encontrado
}

/* Retorna o tamanho da maior lista encadeada presente na tabela */
int hash_maior_lista(Hash *h) {
    int maior = 0;
    for (int i = 0; i < h->m; i++) {
        int tamanho = 0;
        NoHash *atual = h->vetor[i];
        while (atual != NULL) {
            tamanho++;
            atual = atual->prox;
        }
        if (tamanho > maior) {
            maior = tamanho;
        }
    }
    return maior;
}

/* Libera toda a memória alocada pela tabela e suas listas encadeadas */
void hash_libera(Hash *h) {
    if (h == NULL) return;
    for (int i = 0; i < h->m; i++) {
        NoHash *atual = h->vetor[i];
        while (atual != NULL) {
            NoHash *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(h->vetor);
    free(h);
}
