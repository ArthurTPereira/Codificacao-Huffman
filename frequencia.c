#include <stdio.h>
#include <stdlib.h>
#include "frequencia.h"

//Definição da quantidade de caracteres ASCII
#define TAM 257

/* Aloca a memória necessária para a tabela de frequência
 * Input: Nenhum
 * Output: Tabela de frequência alocada
 * Pré-condição: O arquivo existe e foi corretamente aberto
 * Pós-condição: A tabela foi corretamente gerada
 */
static int* alocaTabelaFrequencia() {
    int* vet = (int*) malloc(sizeof(int) * TAM);
    if (vet == NULL) {
        perror("Erro");
        exit(1);
    }
    
    for (int i = 0; i < TAM; i++) {
        vet[i] = 0;
    }

    return vet;
}

int* preencheFrequencia(FILE* arquivo) {
    char c;
    int* vet = alocaTabelaFrequencia();

    fseek(arquivo,0,SEEK_END); //Coloca a posição no fim do arquivo
    unsigned long filelen = ftell(arquivo); //Coleta o tamanho em bytes do arquivo
    fseek(arquivo,0,SEEK_SET); //Coloca a posição no início do arquivo
    unsigned char* buffer = (char*) malloc(filelen); //Aloca o buffer
    fread(buffer,filelen,sizeof(unsigned char),arquivo); //Lê o arquivo e atribui ao buffer

    int i = 0;
    while (i < filelen) {
        vet[(unsigned char)buffer[i]]++;
        i++;
    }
    vet[256]++;
    free(buffer);
    return vet;
}

void liberaTabela(int* vet) {
    free(vet);
}

void escreveTabelaFrequencia(FILE* destino, int* tabela) {
    for (int i = 0; i < TAM; i++) {
        fwrite(&tabela[i],sizeof(int),1,destino);
    }
}