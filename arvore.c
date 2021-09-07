#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define TAM 128

struct arv {
    char caracter;
    int frequencia;
    Arv* esq;
    Arv* dir;
    Arv* prox;
};

struct lista {
    Arv* prim;
    Arv* ult;
};

Arv* alocaNoArv() {
    Arv* no = (Arv*) malloc(sizeof(Arv));
    if (no == NULL) {
        perror("Erro");
        exit(1);
    }

    return no;
    
}

Arv* inicNoArv() {
    Arv* no = alocaNoArv();
    
    no->esq = NULL;
    no->dir = NULL;
    no->prox = NULL;

    return no;
}

Lista* alocaLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    if (lista == NULL) {
        perror("Erro");
        exit(1);
    }

    return lista;
}

Lista* inicLista() {
    Lista* lista = alocaLista();
    lista->prim = NULL;
    lista->ult = NULL;

    return lista;    
}

void insereOrdenadoLista(Lista* lista, Arv* no) {
    Arv* p;
    Arv* t;

    if (lista->prim == NULL) { //Verifica se a lista esta vazia e adiciona no começo
        lista->prim = no;
        lista->ult = no;
    } else if (no->frequencia < lista->prim->frequencia) { //Verifica se o primeiro item é maior que o que deve ser adicionado
        no->prox = lista->prim;
        lista->prim = no;
    } else {
        p = lista->prim;
        t = p->prox;

        while (t != NULL && no->frequencia > t->frequencia) { //Caminha ate a posicao de onde deve ser adicionado
            p = t;
            t = t->prox;
        }

        if (t == NULL) { //Caso seja o ultimo da lista, adiciona no final
            p->prox = no;
            lista->ult = no;
        } else { //Caso seja no meio, insere no meio
            no->prox = t;
            p->prox = no;
        }
    }
}

void preencheLista(Lista* lista, int* vet) {
    Arv* no;
    for (int i = 0; i < TAM; i++) {
        if (vet[i] != 0 && i >= 32 && i <= 126) {
            no = inicNoArv();
            no->caracter = (char)i;
            no->frequencia = vet[i];

            insereOrdenadoLista(lista,no);
        }
    }
}

void imprimeLista(Lista* lista) {
    Arv* p;
    for (p = lista->prim; p != NULL; p = p->prox) {
        printf("%c - %d\n",p->caracter,p->frequencia);
    }
}

void liberaLista(Lista* lista) {
    free(lista);
}

Arv* removePrimElemento(Lista* lista) {
    Arv* p = NULL;

    if (lista->prim != NULL) {
        p = lista->prim;
        lista->prim = p->prox;
        p->prox = NULL;
    }
    
    return p;
}

Arv* geraArv(Lista* lista) {
    Arv* esq;
    Arv* dir;
    Arv* novo;

    while (lista->prim != NULL && lista->prim->prox != NULL) {
        esq = removePrimElemento(lista);
        dir = removePrimElemento(lista);
        
        novo = alocaNoArv();
        novo->prox = NULL;

        novo->frequencia = esq->frequencia + dir->frequencia;
        novo->esq = esq;
        novo->dir = dir;

        insereOrdenadoLista(lista,novo);
    }
    lista->ult = lista->prim;
    return lista->prim;
}

void imprimeArv(Arv* arv) {
    if (arv != NULL) {
        printf("Folha: %c Frequencia: %d\n",arv->caracter,arv->frequencia);
        imprimeArv(arv->esq);
        imprimeArv(arv->dir);
    }
}

Arv* liberaArv(Arv* arv) {
    if (arv != NULL) {
        liberaArv(arv->esq);
        liberaArv(arv->dir);
        free(arv);
        arv = NULL;
    }
    return NULL;
}