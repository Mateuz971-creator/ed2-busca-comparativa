#include <stdlib.h>
#include "hash.h"
#include "medicao.h"

/* ATENÇÃO: As structs 'NoHash' e 'Hash' já vêm definidas em hash.h.
   Portanto, não redefinimos nenhuma struct aqui para evitar conflitos. */

/* Cria a tabela hash com m listas */
Hash *hash_cria(int m) {
    Hash *h = malloc(sizeof(Hash));
    if (h == NULL) return NULL;
    h->m = m;
    h->n = 0;
    h->lista = calloc((size_t)m, sizeof(NoHash *)); // Usa h->lista conforme o header
    if (h->lista == NULL) {
        free(h);
        return NULL;
    }
    return h;
}

/* Função hash h(k) = k % m (conforme protótipo do header) */
int hash_funcao(const Hash *h, int chave) {
    int r = chave % h->m;
    return r < 0 ? r + h->m : r; // Garante índice positivo
}

/* Insere a chave e a posição no INÍCIO da lista encadeada */
void hash_insere(Hash *h, int chave, int pos) {
    int idx = hash_funcao(h, chave);

    NoHash *novo = malloc(sizeof(NoHash));
    if (novo == NULL) return;

    novo->chave = chave;
    novo->pos = pos;
    novo->prox = h->lista[idx];  // Insere no início da lista
    h->lista[idx] = novo;

    h->n++;
}

/* Busca a chave na tabela hash. 
   Regra de contagem: soma 1 a cada nó visitado na lista encadeada. */
int hash_busca(const Hash *h, int chave) {
    int idx = hash_funcao(h, chave);
    NoHash *atual = h->lista[idx];

    while (atual != NULL) {
        comparacoes++; // Soma 1 a cada nó visitado na lista ligada
        if (atual->chave == chave) {
            return atual->pos; // Retorna a posição do aluno no vetor
        }
        atual = atual->prox;
    }

    return -1; // Não encontrado
}

/* Retorna o tamanho do maior lista encadeada na tabela */
int hash_maior_lista(const Hash *h) {
    int maior = 0;
    for (int i = 0; i < h->m; i++) {
        int tamanho = 0;
        NoHash *atual = h->lista[i];
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
        NoHash *atual = h->lista[i];
        while (atual != NULL) {
            NoHash *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(h->lista);
    free(h);
}
