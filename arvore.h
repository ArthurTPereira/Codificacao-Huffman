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


#endif // ARVORE_H