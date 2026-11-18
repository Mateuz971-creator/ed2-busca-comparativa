#include <stddef.h>
#include "arvoreb.h"
#include "medicao.h"

// ========== 1. BUSCA ==========
int arvb_busca(const ArvoreB *a, int chave) {
    if (a->raiz == NULL)
        return -1;
    
    NoB *x = a->raiz;
    while (1) {
        comparacoes++;  // Conta cada NÓ visitado
        
        int i = 0;
        while (i < x->n && chave > x->chave[i])
            i++;
        
        if (i < x->n && chave == x->chave[i])
            return x->pos[i];
        
        if (x->folha)
            return -1;
        
        x = x->filho[i];
    }
}

// ========== 2. DIVIDE FILHO ==========
static void divide_filho(ArvoreB *a, NoB *x, int i) {
    int t = a->t;
    NoB *y = x->filho[i];
    NoB *z = arvb_novo_no(a, y->folha);
    z->n = t - 1;
    
    // Copia as t-1 maiores chaves e posições de y para z
    for (int j = 0; j < t - 1; j++) {
        z->chave[j] = y->chave[j + t];
        z->pos[j] = y->pos[j + t];
    }
    
    // Copia os t últimos filhos, se não for folha
    if (!y->folha) {
        for (int j = 0; j < t; j++)
            z->filho[j] = y->filho[j + t];
    }
    
    y->n = t - 1;
    
    // Abre espaço nos filhos de x
    for (int j = x->n; j >= i + 1; j--)
        x->filho[j + 1] = x->filho[j];
    
    x->filho[i + 1] = z;
    
    // Abre espaço nas chaves e posições de x
    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
        x->pos[j + 1] = x->pos[j];
    }
    
    // Sobe a chave do meio e sua posição
    x->chave[i] = y->chave[t - 1];
    x->pos[i] = y->pos[t - 1];
    x->n++;
}

// ========== 3. INSERE EM NÓ NÃO CHEIO ==========
static void insere_nao_cheio(ArvoreB *a, NoB *x, int k, int v) {
    int i = x->n - 1;
    
    if (x->folha) {
        // Desloca chaves maiores para a direita
        while (i >= 0 && k < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            x->pos[i + 1] = x->pos[i];
            i--;
        }
        x->chave[i + 1] = k;
        x->pos[i + 1] = v;
        x->n++;
    } else {
        // Acha a posição certa para descer
        while (i >= 0 && k < x->chave[i])
            i--;
        i++;
        
        // Se o filho está cheio, divide primeiro
        if (x->filho[i]->n == 2 * a->t - 1) {
            divide_filho(a, x, i);
            if (k > x->chave[i])
                i++;
        }
        insere_nao_cheio(a, x->filho[i], k, v);
    }
}

// ========== 4. INSERE ==========
void arvb_insere(ArvoreB *a, int chave, int pos) {
    // Não insere se a chave já existir
    if (arvb_busca(a, chave) != -1)
        return;
    
    // Árvore vazia
    if (a->raiz == NULL) {
        a->raiz = arvb_novo_no(a, 1);
        a->raiz->chave[0] = chave;
        a->raiz->pos[0] = pos;
        a->raiz->n = 1;
        return;
    }
    
    // Raiz está cheia → árvore cresce em altura
    if (a->raiz->n == 2 * a->t - 1) {
        NoB *s = arvb_novo_no(a, 0);
        s->filho[0] = a->raiz;
        a->raiz = s;
        divide_filho(a, s, 0);
        insere_nao_cheio(a, s, chave, pos);
    } else {
        insere_nao_cheio(a, a->raiz, chave, pos);
    }
}

// ========== 5. ALTURA ==========
int arvb_altura(const ArvoreB *a) {
    if (a->raiz == NULL)
        return 0;
    
    int altura = 1;
    NoB *x = a->raiz;
    while (!x->folha) {
        altura++;
        x = x->filho[0];
    }
    return altura;
}

// ========== 6. DESAFIO: CONTA FAIXA ==========
static int conta_no_intervalo(const NoB *x, int ini, int fim) {
    int total = 0;
    int i = 0;
    
    // Conta as chaves neste nó que estão no intervalo
    while (i < x->n && x->chave[i] <= fim) {
        if (x->chave[i] >= ini)
            total++;
        i++;
    }
    
    // Se for folha, acabou
    if (x->folha)
        return total;
    
    // Encontra o primeiro filho que pode ter valores no intervalo
    int inicio = 0;
    while (inicio < x->n && ini > x->chave[inicio])
        inicio++;
    
    // Encontra o último filho que pode ter valores no intervalo
    int fim_idx = x->n;
    while (fim_idx > 0 && fim < x->chave[fim_idx - 1])
        fim_idx--;
    
    // Desce apenas nos filhos necessários
    for (int j = inicio; j <= fim_idx; j++)
        total += conta_no_intervalo(x->filho[j], ini, fim);
    
    return total;
}

int arvb_conta_faixa(const ArvoreB *a, int ini, int fim) {
    if (a->raiz == NULL)
        return 0;
    return conta_no_intervalo(a->raiz, ini, fim);
}
