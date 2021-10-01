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

/* Retorna o nó esquerdo de um nó de árvore
 * Input: Ponteiro para um nó
 * Output: Ponteiro para o nó esquerdo
 * Pré-condição: A árvore existe e está corretamente alocada
 * Pós-condição: A árvore permanece inalterada
 */
Arv* retornaArvEsq(Arv* arv);

/* Retorna o nó direito de um nó de árvore
 * Input: Ponteiro para um nó
 * Output: Ponteiro para o nó direito
 * Pré-condição: A árvore existe e está corretamente alocada
 * Pós-condição: A árvore permanece inalterada
 */
Arv* retornaArvDir(Arv* arv);

/* Retorna o caractere de um nó de árvore
 * Input: Ponteiro para um nó
 * Output: Caractere do nó
 * Pré-condição: A árvore existe e está corretamente alocada
 * Pós-condição: A árvore permanece inalterada
 */
unsigned char retornaArvCaracter(Arv* arv);

/* Retorna o parâmetro EOF de um nó de árvore
 * Input: Ponteiro para um nó
 * Output: Parâmetro EOF
 * Pré-condição: A árvore existe e está corretamente alocada
 * Pós-condição: A árvore permanece inalterada
 */
int retornaArvEOF(Arv* arv);

/* Retorna a frequência de um nó de árvore
 * Input: Ponteiro para um nó
 * Output: Frequência do nó
 * Pré-condição: A árvore existe e está corretamente alocada
 * Pós-condição: A árvore permanece inalterada
 */
int retornaArvFreq(Arv* arv);

#endif // ARVORE_H