
#include "ordenacao.h"
#include "medicao.h"

/* ===================== TAREFA 1: ORDENAÇÃO ===================== */

/* Insertion Sort */
void ordena_insercao(Aluno *v, int n) {

    for (int i = 1; i < n; i++) {

        Aluno x = v[i];
        int j = i - 1;

        while (j >= 0) {

            comparacoes++;

            if (v[j].matricula > x.matricula) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }

        v[j + 1] = x;
    }
}

/* Função auxiliar do Quicksort */
static void quick(Aluno *v, int ini, int fim) {

    int i = ini;
    int j = fim;

    int pivo = v[ini + (fim - ini) / 2].matricula;

    while (i <= j) {

        while (i <= fim) {
            comparacoes++;

            if (v[i].matricula < pivo) {
                i++;
            } else {
                break;
            }
        }

        while (j >= ini) {
            comparacoes++;

            if (v[j].matricula > pivo) {
                j--;
            } else {
                break;
            }
        }

        if (i <= j) {
            Aluno temp = v[i];
            v[i] = v[j];
            v[j] = temp;

            i++;
            j--;
        }
    }

    if (ini < j) {
        quick(v, ini, j);
    }

    if (i < fim) {
        quick(v, i, fim);
    }
}

/* Quicksort */
void ordena_quick(Aluno *v, int n) {

    if (n > 1) {
        quick(v, 0, n - 1);
    }
}
