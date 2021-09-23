#ifndef ARVORE_H
#define ARVORE_H

// Definição da estrutura da árvore
typedef struct arv Arv;

// Definição da estrutura da lista encadeada
typedef struct lista Lista;

/* Inicializa um nó de uma árvore
 * Input: Nenhum
 * Output: Ponteiro para memória alocada de um nó da árvore
 * Pré-condição: Nenhum
 * Pós-condição: A memória foi corretamente alocada
 */
Arv* inicNoArv();

/* Inicializa uma lista encadeada
 * Input: Nenhum
 * Output: Ponteiro para memória alocada de uma lista encadeada
 * Pré-condição: Nenhum
 * Pós-condição: A memória foi corretamente alocada
 */
Lista* inicLista();

/* Preenche a lista encadeada com os nós da árvore e suas frequências
 * Input: Ponteiro para a lista encadeada e o vetor de frequência
 * Output: Nenhum
 * Pré-condição: A lista encadeada e o vetor de frequência existem, e estão corretamente alocados
 * Pós-condição: A lista encadeada foi corretamente preenchida
 */
void preencheLista(Lista* lista, int* vet);

void imprimeLista(Lista* lista); // Função temporária

/* Libera a memória alocada de uma lista encadeada
 * Input: Ponteiro para a lista encadeada
 * Output: Nenhum
 * Pré-condição: A lista encadeada existe e está alocada
 * Pós-condição: A memória foi corretamente liberada
 */
void liberaLista(Lista* lista);

/* Converte a lista encadeada com as frequências para a árvore de Huffman
 * Input: Ponteiro para a lista encadeada
 * Output: Ponteiro para a raiz da árvore de Huffman
 * Pré-condição: A lista encadeada existe e está corretamente alocada
 * Pós-condição: A árvore foi corretamente gerada, e a lista encadeada possui apenas a posição da raiz da árvore
 */
Arv* geraArv(Lista* lista);

void imprimeArv(Arv* arv); // Função temporária

/* Libera a memória alocada de uma árvore
 * Input: Ponteiro para a raiz de uma árvore
 * Output: Nenhum
 * Pré-condição: A árvore existe e está corretamente alocada
 * Pós-condição: A memória foi corretamente liberada
 */
void liberaArv(Arv* arv);

/* Retorna a altura de uma árvore
 * Input: Ponteiro para a raiz da árvore
 * Output: Altura da árvore
 * Pré-condição: A árvore existe e está corretamente alocada
 * Pós-condição: A árvore permanece inalterada
 */
int retornaAltura(Arv* arv);

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

void imprimeDicionario(char** dic); // Função temporária

/* Libera a memória alocada de um dicionário
 * Input: Ponteiro para o dicionário
 * Output: Nenhum
 * Pré-condição: O dicionário existe e está alocadp
 * Pós-condição: A memória foi corretamente liberadasss
 */
void liberaDicionario(char** dic);

void compacta(char** dicionario, FILE* origem, char* filename, int* tabela);

void descompacta(char* filename);

#endif // ARVORE_H