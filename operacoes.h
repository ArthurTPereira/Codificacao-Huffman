#ifndef OPERACOES_H
#define OPERACOES_H

#include "arvore.h"

/* Compacta um arquivo
 * Input: Ponteiro para o dicionário, o arquivo a ser compactado, o nome do arquivo e a tabela de frequência
 * Output: Nenhum
 * Pré-condição: O dicionário, o arquivo, o nome e a tabela existem e estão corretamente alocados e criados
 * Pós-condição: O arquivo compactado é criado, e nada mais é alterado.
 */
void compacta(char** dicionario, FILE* origem, char* filename, int* tabela);

/* Descompacta um arquivo
 * Input: Ponteiro para o arquivo a ser descompactado, a árvore de huffman,o nome do arquivo e a extensao
 * Output: Nenhum
 * Pré-condição: O arquivo, a árvore e o nome existem e estão corretamente alocados e criados
 * Pós-condição: O arquivo foi descompactado, e nada mais é alterado
 */
void descompacta(FILE* arquivo, Arv* huffman, char* filename, char* extensao);




#endif //OPERACOES_H