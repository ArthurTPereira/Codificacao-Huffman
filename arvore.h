#ifndef ARVORE_H
#define ARVORE_H

typedef struct arv Arv;

typedef struct lista Lista;

Arv* inicNoArv();

Lista* inicLista();

void preencheLista(Lista* lista, int* vet);

void imprimeLista(Lista* lista); // Função temporária

void liberaLista(Lista* lista);

Arv* geraArv(Lista* lista);

void imprimeArv(Arv* arv); // Função temporária

Arv* liberaArv(Arv* arv);

int retornaAltura(Arv* arv);

char** alocaDicionario(int col);

void criaDicionario(char** dic, Arv* arv, char* codigo, int col);

void imprimeDicionario(char** dic); // Função temporária

void liberaDicionario(char** dic);

#endif // ARVORE_H