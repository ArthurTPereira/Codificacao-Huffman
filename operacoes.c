#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"
#include "arvore.h"
#include "operacoes.h"
#include "frequencia.h"

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
            //Escreve todo o conteúdo do bitmap no arquivo
            fwrite(&bitmapGetContents(bm)[i],sizeof(unsigned char),1,destino);
        }
        bitmapLibera(bm);
        bm = bitmapInit(80000000);
        return bm;
}

/* Escreve um bit em um arquivo
 * Input: Ponteiro para o arquivo, para o bitmap e um bit
 * Output: Nenhum
 * Pré-condição: O arquivo e o bitmap existem e estão corretamente alocados, e o bit é válido
 * Pós-condição: Nenhum
 */
static void escreve(FILE* destino,bitmap* bm, unsigned char bit) {
    if (verificaTamanho(bm) == 1) { // Verifica se o bitmap está cheio
        bm = recriaBitmap(destino,bm);
    } else if (bit == 1) {
        bitmapAppendLeastSignificantBit(bm,1); // Adiciona o bit 1 e verifica se o bitmap está cheio
        if (verificaTamanho(bm) == 1) {
            bm = recriaBitmap(destino,bm);
        }
    } else {
        bitmapAppendLeastSignificantBit(bm,0); // Adiciona o bit 0 e verifica se o bitmap está cheio
        if (verificaTamanho(bm) == 1) {
            bm = recriaBitmap(destino,bm);
        }
    }
}

void compacta(char** dicionario, FILE* origem, char* filename, int* tabela) {
    //Coleta o nome do arquivo e a extensão, e insere a extensão .comp no final
    char temp[100];
    char nome[100];
    unsigned char ext[10];
    strcpy(temp,filename);
    char* pt = strtok(temp,".");
    strcpy(nome,pt);
    pt = strtok(NULL,".");
    strcpy(ext,pt);
    strcat(nome,".comp");
    int k = (int)strlen(ext);

    FILE* comp = fopen(nome,"wb");
    if (comp == NULL) {
        perror("Erro");
    }
    fwrite(&k,sizeof(int),1,comp); // Escreve o número de caracteres da extensão
    fwrite(&ext,sizeof(char),k,comp); // Escreve a extensão
    escreveTabelaFrequencia(comp,tabela);

    fseek(origem,0,SEEK_SET);
    fseek(origem,0,SEEK_END);
    unsigned long fileLen = ftell(origem);
    fseek(origem,0,SEEK_SET);
    unsigned char* buffer = (char*) malloc(fileLen); //Aloca o buffer

    fread(buffer,fileLen,sizeof(unsigned char),origem); // Lê para o buffer

    char codigo[100];
    strcpy(codigo,"");

    int i = 0;
    int j = 0;

    bitmap* bm = bitmapInit(8000000); //8kk bits == 1MB

    while (i < fileLen) {
        j = 0;
        strcpy(codigo,dicionario[(unsigned char)buffer[i]]); // Copia o código do dicionário para a variável
        while (codigo[j] != '\0') { // Verifica para cada bit do código
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
    while (dicionario[256][j] != '\0') { // Escreve o caractere de final de arquivo
        if (dicionario[256][j] == '1') {
            escreve(comp,bm,1);
        } else if (dicionario[256][j] == '0') {
            escreve(comp,bm,0);
        }
        j++;
    }

    if (bitmapGetLength(bm) % 8 != 0) { // Preenche com zeros no final do último byte caso não seja múltiplo de 8
        n = 8 - (bitmapGetLength(bm) % 8);
        for (i = 0 ; i < n; i++) {
            bitmapAppendLeastSignificantBit(bm,0);
        }        
    }
    
    for (i = 0; i < bitmapGetLength(bm)/8; i++) { // Escreve o bitmap
        fwrite(&bitmapGetContents(bm)[i],sizeof(unsigned char),1,comp);
    }
    
    free(buffer);
    bitmapLibera(bm);
    fclose(comp);
}

/* Verifica se um bit é um
 * Input: Um byte e uma posição
 * Output: 0 se o bit for zero, qualquer valor maior que 0 se o bit for 1
 * Pré-condição: Nenhum
 * Pós-condição: Nenhum
 */
static unsigned int verificaBitUm(unsigned char byte, int i) {
    unsigned char param = (1 << i);
    return byte & param;
}

void descompacta(FILE* arquivo, Arv* huffman, char* filename, char* extensao) {
    //Coleta o nome do arquivo e a extensão, e prepara para criar o arquivo original
    unsigned char c;
    unsigned char d;
    Arv* no = huffman;
    char temp[100];
    char nome[100];
    strcpy(temp,filename);
    strtok(temp,".");
    strcpy(nome,temp);
    strcat(nome,".");
    strcat(nome,extensao);

    FILE* novo = fopen(nome,"wb");
    if (novo == NULL) {
        perror("Erro");
    }

    while (fread(&c,sizeof(unsigned char),1,arquivo)) {
        for (int i = 7; i >= 0; i--) {
            if (verificaBitUm(c,i) > 0) { // Verifica se o bit na posição i é um
                no = retornaArvDir(no);
            } else {
                no = retornaArvEsq(no);
            }

            if (retornaArvEsq(no) == NULL && retornaArvDir(no) == NULL) { // Verifica se é um nó folha
                if (retornaArvEOF(no) == 1) { // Verifica se é o caractere de fim de arquivo
                    fclose(novo);
                    return;
                }
                d = retornaArvCaracter(no);
                fwrite(&d,sizeof(unsigned char),1,novo); // Escreve no arquivo descompactado
                no = huffman;
            }
        }
    }
    fclose(novo);
}