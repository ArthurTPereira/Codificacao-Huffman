#ifndef FREQUENCIA_H
#define FREQUENCIA_H

/* Preenche uma tabela de frequência
 * Input: Ponteiro para o arquivo
 * Output: Tabela de frequência preenchida
 * Pré-condição: O arquivo existe e foi corretamente aberto
 * Pós-condição: A tabela foi corretamente gerada
 */
int* preencheFrequencia(FILE* arquivo);

/* Libera a tabela de frequência
 * Input: Ponteiro para a tabela de frequência
 * Output: Nenhum
 * Pré-condição: A tabela de frequência existe e está corretamente alocada
 * Pós-condição: A memória foi corretamente liberada
 */
void liberaTabela(int* vet);

/* Escreve a tabela de frequência em um arquivo
 * Input: Ponteiro para o arquivo aberto e a tabela de frequência
 * Output: Nenhum
 * Pré-condição: O arquivo e a tabela existem e estão corretamente alocados
 * Pós-condição: A tabela foi escrita no arquivo corretamente
 */
void escreveTabelaFrequencia(FILE* destino, int* tabela);

#endif // FREQUENCIA_H