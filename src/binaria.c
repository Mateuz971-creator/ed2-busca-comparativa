
#include "binaria.h"
#include "medicao.h"

/* ===================== TAREFA 2: Busca Binária - implementação ===================== */

int busca_binaria(const Aluno *v, int n, int mat) {

    int ini = 0;
    int fim = n - 1;

    while (ini <= fim) {

        int meio = ini + (fim - ini) / 2;

        comparacoes++;

        if (v[meio].matricula == mat) {
            return meio;
        }

        if (v[meio].matricula < mat) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}
