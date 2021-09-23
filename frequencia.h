#ifndef FREQUENCIA_H
#define FREQUENCIA_H

/* Preenche uma tabela de frequência
 * Input: Ponteiro para o arquivo
 * Output: Tabela de frequência
 * Pré-condição: O arquivo existe e foi corretamente aberto
 * Pós-condição: A tabela foi corretamente gerada
 */
int* preencheFrequencia(FILE* arquivo);

void imprimeTabelaFrequencia(int* vet); // Função temporária

/* Libera a tabela de frequência
 * Input: Ponteiro para a tabela de frequência
 * Output: Nenhum
 * Pré-condição: A tabela de frequência existe e está corretamente alocada
 * Pós-condição: A memória foi corretamente liberada
 */
void liberaTabela(int* vet);

#endif // FREQUENCIA_H