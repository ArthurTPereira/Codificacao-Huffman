#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "frequencia.h"
#include "dicionario.h"

//Definição da quantidade de caracteres ASCII
#define TAM 257

struct arv {
    unsigned char caracter;
    int frequencia;
    int eof;
    Arv* esq;
    Arv* dir;
    Arv* prox;
};

struct lista {
    Arv* prim;
    Arv* ult;
};

/* Aloca a memória para um nó de uma árvore
 * Input: Nenhum
 * Output: Ponteiro para o nó alocado
 * Pré-condição: Nenhum
 * Pós-condição: A memória foi corretamente alocada
 */
static Arv* alocaNoArv() {
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

/* Aloca a memória para uma lista encadeada
 * Input: Nenhum
 * Output: Ponteiro para a lista encadeada alocada
 * Pré-condição: Nenhum
 * Pós-condição: A memória foi corretamente alocada
 */
static Lista* alocaLista() {
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
        if (vet[i] > 0) { // Adiciona somente os que possuem frequencia maior que zero
            no = inicNoArv();
            no->caracter = (char)i;
            no->frequencia = vet[i];
            no->eof = 0;
            if (i == 256) { // Caso seja o caractere que representa o fim do arquivo
                no->caracter = '\0';
                no->eof = 1;
            }

            insereOrdenadoLista(lista,no); // Insere o novo nó na lista
        }
    }
}

void liberaLista(Lista* lista) {
    free(lista); // Basta liberar a sentinela da lista
}

/* Remove o primeiro elemento da lista encadeada
 * Input: Ponteiro para a lista encadeada
 * Output: Ponteiro para o primeiro elemento da lista removido
 * Pré-condição: A lista existe e está corretamente alocada
 * Pós-condição: Somente o primeiro elemento foi removido, e a lista não foi quebrada
 */
static Arv* removePrimElemento(Lista* lista) {
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
        //Remove os dois primeiros elementos da lista
        esq = removePrimElemento(lista);
        dir = removePrimElemento(lista);
        
        //Cria um novo nó, atribui a esquerda e direita e insere novamente na lista
        novo = alocaNoArv();
        novo->prox = NULL;
        novo->caracter = '\0';
        novo->frequencia = esq->frequencia + dir->frequencia;
        novo->esq = esq;
        novo->dir = dir;

        insereOrdenadoLista(lista,novo);
    }
    lista->ult = lista->prim;
    return lista->prim;
}

void liberaArv(Arv* arv) {
    if (arv != NULL) {
        liberaArv(arv->esq);
        liberaArv(arv->dir);
        free(arv);
        arv = NULL;
    }
}

int retornaAltura(Arv* arv) {
    if (arv == NULL) {
        return 0;
    }

    int esq = retornaAltura(arv->esq);
    int dir = retornaAltura(arv->dir);

    if (esq > dir) {
        return esq + 1;
    } else return dir + 1;
}

Arv* retornaArvEsq(Arv* arv) {
    return arv->esq;
}

Arv* retornaArvDir(Arv* arv) {
    return arv->dir;
}

unsigned char retornaArvCaracter(Arv* arv) {
    return arv->caracter;
}

int retornaArvEOF(Arv* arv) {
    return arv->eof;
}

int retornaArvFreq(Arv* arv) {
    return arv->frequencia;
}