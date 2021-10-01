#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

//Definição da quantidade de caracteres ASCII
#define TAM 257

char** alocaDicionario(int col) {
    char** dic = (char**) malloc(TAM * sizeof(char*));
    if (dic == NULL) {
        perror("Erro");
        exit(1);
    }

    for (int i = 0; i < TAM; i++) {
        dic[i] = calloc(col,sizeof(char)); //Inicia as strings do dicionário vazias
    }
    
    return dic;
}

void criaDicionario(char** dic, Arv* arv, char* codigo, int altura) {
    char esq[altura]; //Tamanho máximo do código = altura da árvore
    char dir[altura];
        
    if (retornaArvEsq(arv) == NULL && retornaArvDir(arv) == NULL) {
        if (retornaArvEOF(arv) == 1) { //Verifica se é o caractere de fim de arquivo
            strcpy(dic[256],codigo);
        } else {
            strcpy(dic[retornaArvCaracter(arv)],codigo);
        }
    } else {
        strcpy(esq,codigo);
        strcpy(dir,codigo);
        strcat(esq,"0"); //Concatena 0 ao ir para a esquerda
        strcat(dir,"1"); //Concatena 1 ao ir para a direita

        criaDicionario(dic,retornaArvEsq(arv),esq,altura);
        criaDicionario(dic,retornaArvDir(arv),dir,altura);
    }
}

void liberaDicionario(char** dic) {
    for (int i = 0; i < TAM; i++) {
        free(dic[i]);
        dic[i] = NULL;
    }
    free(dic);
    dic = NULL;
}