#include <stdio.h>
#include <stdlib.h>
#include "frequencia.h"

#define TAM 128

int* alocaTabelaFrequencia() {
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
    while(fscanf(arquivo,"%c",&c) == 1) {
        vet[c]++;
    }

    return vet;
}

void imprimeTabelaFrequencia(int* vet) {
    for (int i = 0; i < TAM; i++) {
        if (vet[i] != 0 && i >= 32 && i <= 126) {
            printf("%c - %d\n",i,vet[i]);
        }
    }
}

void liberaTabela(int* vet) {
    free(vet);
}