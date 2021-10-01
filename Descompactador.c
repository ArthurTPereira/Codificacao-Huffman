#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequencia.h"
#include "arvore.h"
#include "dicionario.h"
#include "operacoes.h"

int main(int argc, char* argv[]) {

    //Abre o arquivo a ser descompactado
    FILE* compactado = fopen(argv[1],"rb");
    if (compactado == NULL) {
        perror("Erro");
    }

    int i;

    //Lê o inteiro que define a quantidade de caracteres da extensão do arquivo
    fread(&i,sizeof(int),1,compactado);
    
    static char ext[10];

    //Lê a extensão do arquivo
    fread(&ext,sizeof(char),i,compactado);

    int frequencia[257];

    //Lê a tabela de frequência
    fread(frequencia,sizeof(int),257,compactado);
    Lista* lista = inicLista();

    //Preenche a lista encadeada com a tabela de frequência
    preencheLista(lista,frequencia);

    //Gera a árvore de Huffman a partir da lista encadeada
    Arv* huffman = geraArv(lista);

    //Descompacta o arquivo
    descompacta(compactado,huffman,argv[1],ext);

    //Libera a memória
    liberaArv(huffman);
    liberaLista(lista);
    fclose(compactado);

    return 0;
}