
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
