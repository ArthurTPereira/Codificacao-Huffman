#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "frequencia.h"

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
        if (vet[i] != 0) {
            no = inicNoArv();
            no->caracter = (char)i;
            no->frequencia = vet[i];
            no->eof = 0;
            if (i == 256) {
                no->caracter = '\0';
                no->eof = 1;
            }

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
        esq = removePrimElemento(lista);
        dir = removePrimElemento(lista);
        
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

void imprimeArv(Arv* arv) {
    if (arv != NULL) {
        printf("Folha: %c Frequencia: %d\n",arv->caracter,arv->frequencia);
        imprimeArv(arv->esq);
        imprimeArv(arv->dir);
    }
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

char** alocaDicionario(int col) {
    char** dic = (char**) malloc(TAM * sizeof(char*));
    if (dic == NULL) {
        perror("Erro");
        exit(1);
    }

    for (int i = 0; i < TAM; i++) {
        dic[i] = calloc(col,sizeof(char));
    }
    
    return dic;
}

void criaDicionario(char** dic, Arv* arv, char* codigo, int altura) {
    char esq[altura]; //Tamanho máximo do código = altura da árvore
    char dir[altura];
    
    if (arv->esq == NULL && arv->dir == NULL) {
        if (arv->eof == 1) {
            strcpy(dic[256],codigo);
        } else {
            strcpy(dic[arv->caracter],codigo);
        }
    } else {
        strcpy(esq,codigo);
        strcpy(dir,codigo);
        strcat(esq,"0");
        strcat(dir,"1");

        criaDicionario(dic,arv->esq,esq,altura);
        criaDicionario(dic,arv->dir,dir,altura);
    }
}

void imprimeDicionario(char** dic) {
    for (int i = 0; i < TAM; i++) {
        //if (*dic[i] != '\0') {
            printf("%d - %s\n",i,dic[i]);
        //}
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

/* Verifica se o bitmap está com tamanho cheio
 * Input: Ponteiro para o bitmap
 * Output: Booleano: 1 se estiver cheio, 0 se estiver vazio
 * Pré-condição: O bitmap existe e está corretamente alocado
 * Pós-condição: Nenhum
 */
static int verificaTamanho(bitmap* bm) {
    if (bitmapGetLength(bm) == bitmapGetMaxSize(bm)) {
        return 1;
    } else {
        return 0;
    }
}

/* Escreve todo o bitmap em um arquivo e realoca a sua memória
 * Input: Ponteiro para o arquivo a ser escrito e ponteiro para o bitmap
 * Output: Ponteiro para o bitmap realocado
 * Pré-condição: O bitmap e o arquivo existem e estão corretamente alocados
 * Pós-condição: A memória do bitmap é realocada, e o arquivo permanece aberto
 */
static bitmap* recriaBitmap(FILE* destino, bitmap* bm) {
        for (int i = 0; i < bitmapGetLength(bm)/8; i++) {
            fwrite(&bitmapGetContents(bm)[i],sizeof(unsigned char),1,destino);
        }
        bitmapLibera(bm);
        bm = bitmapInit(80000000);
        printf("Bitmap recriado\n");
        return bm;
}

/* Escreve um bit em um arquivo
 * Input: Ponteiro para o arquivo, para o bitmap e um bit
 * Output: Nenhum
 * Pré-condição: O arquivo e o bitmap existem e estão corretamente alocados, e o bit é válido
 * Pós-condição: Nenhum
 */
static void escreve(FILE* destino,bitmap* bm, unsigned char bit) {
    if (verificaTamanho(bm) == 1) {
        bm = recriaBitmap(destino,bm);
    } else if (bit == 1) {
        bitmapAppendLeastSignificantBit(bm,1);
        if (verificaTamanho(bm) == 1) {
            bm = recriaBitmap(destino,bm);
        }
    } else {
        bitmapAppendLeastSignificantBit(bm,0);
        if (verificaTamanho(bm) == 1) {
            bm = recriaBitmap(destino,bm);
        }
    }
}

void compacta(char** dicionario, FILE* origem, char* filename, int* tabela) {
    char nome[100];
    strcpy(nome,filename);
    strtok(nome,".");
    strcat(nome,".comp");

    FILE* comp = fopen(nome,"ab");
    if (comp == NULL) {
        perror("Erro");
    }
    escreveTabelaFrequencia(comp,tabela);

    fseek(origem,0,SEEK_SET);
    fseek(origem,0,SEEK_END);
    unsigned long filelen = ftell(origem);
    fseek(origem,0,SEEK_SET);
    unsigned char* buffer = (char*) malloc(filelen);

    fread(buffer,filelen,sizeof(unsigned char),origem);

    char codigo[100];
    strcpy(codigo,"");

    int i = 0;
    int j = 0;

    bitmap* bm = bitmapInit(80000000); //8kk bits == 1MB

    while (i < filelen) {
        j = 0;
        strcpy(codigo,dicionario[(unsigned char)buffer[i]]);
        while (codigo[j] != '\0') {
            if (codigo[j] == '1') {
                escreve(comp,bm,1);
            } else if (codigo[j] == '0') {
                escreve(comp,bm,0);
            }
            j++;
        }
        i++;
    }

    int n;
    j = 0;
    while (dicionario[256][j] != '\0') {
        if (dicionario[256][j] == '1') {
            escreve(comp,bm,1);
        } else if (dicionario[256][j] == '0') {
            escreve(comp,bm,0);
        }
        j++;
    }

    if (bitmapGetLength(bm) % 8 != 0) {
        n = 8 - (bitmapGetLength(bm) % 8);
        for (i = 0 ; i < n; i++) {
            bitmapAppendLeastSignificantBit(bm,0);
        }        
    }
    
    for (i = 0; i < bitmapGetLength(bm)/8; i++) {
        fwrite(&bitmapGetContents(bm)[i],sizeof(unsigned char),1,comp);
    }
    
    free(buffer);
    bitmapLibera(bm);
    fclose(comp);
}

static unsigned int verificaBitUm(unsigned char byte, int i) {
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

void descompacta(FILE* arquivo, Arv* huffman, char* filename) {
    unsigned char c;
    Arv* no = huffman;

    char nome[100];
    strcpy(nome,filename);
    strtok(nome,".");
    strcat(nome,"2.txt");
    FILE* novo = fopen(nome,"wb");
    if (novo == NULL) {
        perror("Erro");
    }

    while (fread(&c,sizeof(unsigned char),1,arquivo)) {
        for (int i = 7; i >= 0; i--) {
            if (verificaBitUm(c,i)) {
                no = no->dir;
            } else {
                no = no->esq;
            }

            if (no->esq == NULL && no->dir == NULL) {
                if (no->eof == 1) {
                    fclose(novo);
                    return;
                }
                
                fwrite(&no->caracter,sizeof(unsigned char),1,novo);
                no = huffman;
            }
        }
    }
    fclose(novo);
}