#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "arvore.h"

/* Faz a alocação de um dicionário
 * Input: Número de colunas do dicionário
 * Output: Ponteiro para o dicionário
 * Pré-condição: Nenhum
 * Pós-condição: A memória foi corretamente alocada
 */
char** alocaDicionario(int col);

/* Preenche o dicionário com os códigos de cada posição
 * Input: Ponteiro para o dicionário, ponteiro para a árvore de Huffman, ponteiro para o código da posição e a altura da árvore
 * Output: Nenhum
 * Pré-condição: O dicionário e a árvore existem e estão corretamente alocados
 * Pós-condição: O dicionário foi preenchido corretamente
 */
void criaDicionario(char** dic, Arv* arv, char* codigo, int altura);

/* Libera a memória alocada de um dicionário
 * Input: Ponteiro para o dicionário
 * Output: Nenhum
 * Pré-condição: O dicionário existe e está alocado
 * Pós-condição: A memória foi corretamente liberada
 */
void liberaDicionario(char** dic);

#endif //DICIONARIO_H