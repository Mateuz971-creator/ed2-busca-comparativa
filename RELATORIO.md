# Relatório: Comparativo de Estruturas de Busca

Grupo: Elas e Ele

Integrantes: Mateus Batista, Raika Maciel, Raica da Silva, Victoria Batalha.

Copiem os valores da coluna **Comparacoes/busca** (e dos Detalhes, quando pedido). Os tempos são opcionais, porque variam de um computador para outro.

## E1. Crescimento de N (t = 3, alfa = 1)

| N | Sequencial | Binária | Hash | Árvore-B |
| --- | --- | --- | --- | --- |
| 10.000 |7465.45|12.87|1.24|6.85|
| 50.000 |37618.52|15.16|1.21|7.85|
| 100.000 |75401.71|16.19|1.19|8.84|
| 200.000 |150176.39|17.18|1.13|8.84|

**Perguntas**

1. Na busca sequencial, quantas comparações são feitas quando a matrícula existe? E quando não existe? Usem isso para explicar por que a média fica perto de 0,75 × N.

   Na busca sequencial, quando a matrícula existe, são feitas em média aproximadamente N/2 comparações, pois o aluno pode estar em qualquer posição. Quando não existe, é necessário percorrer os N elementos. Como metade das consultas existe e metade não existe, a média fica próxima de 0,75 × N.

2. Calculem log₂ N para cada N e comparem com a coluna da binária. O que acontece com as comparações quando N dobra?

   Os valores aproximados de log₂ N são 13,29 para 10.000; 15,61 para 50.000; 16,61 para 100.000; e 17,61 para 200.000. Os valores medidos na busca binária ficaram próximos desses números. Quando N dobra, o número de comparações aumenta aproximadamente uma unidade, mostrando crescimento logarítmico.

3. Qual estrutura quase não muda quando N cresce? Por quê?

   A tabela hash foi a estrutura que apresentou menor variação no número de comparações, ficando entre 1,13 e 1,24. Isso acontece porque a função hash permite acessar diretamente uma lista associada à matrícula, mantendo o número médio de comparações próximo de uma constante quando o fator de carga é controlado.

## E2. Ordenação

| Algoritmo | N | Comparações | Tempo (s) |
| --- | --- | --- | --- |
| Inserção | 10.000 |25257925|0.1350|
| Quicksort | 10.000 |179055|0.0020|
| Quicksort | 100.000 |2228115|0.0200|

**Perguntas**

4. Quantas vezes a Inserção fez mais comparações que o Quicksort com N = 10.000? Relacionem com as complexidades O(n²) e O(n log n).

   Com N = 10.000, a ordenação por Inserção realizou aproximadamente 141 vezes mais comparações que o Quicksort. Isso ocorre porque a Inserção apresenta complexidade O(n²) no caso médio, enquanto o Quicksort apresenta complexidade média O(n log n), sendo mais eficiente para grandes quantidades de dados.

5. Para usar a busca binária é preciso ordenar antes. Com N = 100.000, depois de quantas buscas o custo do Quicksort "se paga", comparado a fazer só buscas sequenciais? Mostrem a conta.

   Para N = 100.000, o Quicksort realizou 2.228.115 comparações para ordenar o vetor. A busca sequencial realizou, em média, 75.401,71 comparações por busca, enquanto a busca binária realizou 16,19.
Dividindo o custo da ordenação pela economia de comparações em cada busca, temos:
2.228.115 / (75.401,71 - 16,19) ≈ 29,56

Portanto, após aproximadamente 30 buscas, o custo inicial da ordenação é compensado pela economia de comparações proporcionada pela busca binária. Esse resultado é uma estimativa baseada no número de comparações, e não no tempo de execução.


## E3. Grau da Árvore-B (N = 100.000)

| t | Máx. chaves por nó | Altura | Nós | Nós visitados por busca |
| --- | --- | --- | --- | --- |
| 2 |3|13|57124|  |
| 3 |5|9|31298|  |
| 10 |19|5|7666|  |
| 50 |99|3|1482|  |

**Perguntas**

6. Por que a altura cai quando t aumenta?

   A altura da Árvore-B diminui quando o grau mínimo aumenta porque cada nó pode armazenar mais chaves e possuir mais filhos. Assim, a mesma quantidade de registros pode ser organizada em menos níveis. Nos testes, a altura caiu de 13, com t = 2, para 3, com t = 50.

7. Com t = 50, cada nó visitado pode exigir até 99 comparações dentro do nó. Mesmo assim, por que bancos de dados usam árvores com nós grandes? Pensem em cada nó como uma leitura de disco.

   Os bancos de dados utilizam árvores com nós grandes porque o acesso ao disco é mais demorado do que as comparações feitas dentro de um nó. Mesmo que um nó tenha muitas chaves, a árvore fica com menos níveis, reduzindo a quantidade de leituras de disco necessárias para encontrar um registro. Por isso, árvores com nós maiores podem ser mais eficientes em bancos de dados.

## E4. Fator de carga da hash (N = 100.000)

| alfa | m (listas) | Comparações por busca | Maior lista |
| --- | --- | --- | --- |
| 0,5 |200003|0.82|5|
| 1 |100003|1.19|7|
| 2 |50021|1.92|9|
| 5 |20011|4.14|16|

**Perguntas**

8. A teoria diz que, no encadeamento, uma busca com sucesso faz em média cerca de 1 + alfa/2 comparações e uma busca sem sucesso faz cerca de alfa. Como metade das consultas existe, qual seria a média teórica para cada alfa? Comparem com o medido.

   Considerando metade das buscas com sucesso e metade sem sucesso, a média teórica de comparações é 0,5 + 0,75 × alfa.
   
| Alfa (α) | Média teórica | Média medida |
|---|---|---|
| 0,5 | 0,875 | 0,82 |
| 1 | 1,25 | 1,19 |
| 2 | 2,00 | 1,92 |
| 5 | 4,25 | 4,14 |

  Os resultados ficaram próximos dos valores teóricos e mostram que, conforme o fator de carga aumenta, o número médio de comparações também aumenta.

9. Por que é possível ter comparação por busca menor que 1?
  
   É possível ter menos de uma comparação por busca porque algumas matrículas pesquisadas não existem e podem cair em listas vazias da tabela hash. Nesses casos, o programa identifica que a matrícula não está cadastrada sem precisar comparar nenhuma chave. Isso reduz a média geral de comparações por busca.

## Conclusão

10. Qual estrutura vocês escolheriam em cada situação? Justifiquem.
    1. Sistema que só busca alunos pela matrícula, com o cadastro inteiro na memória.
    2. Relatório que lista os alunos em ordem de matrícula ou por faixa (ex.: todos os ingressantes de 2024).
    3. Índice de um banco de dados guardado em disco, com milhões de registros.

## Divisão do trabalho

| Integrante | O que fez |
| --- | --- |
|  |  |
|  |  |
|  |  |
