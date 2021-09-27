#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequencia.h"
#include "arvore.h"

int main(int argc, char* argv[]) {
    FILE* compactado = fopen(argv[1],"rb");
    if (compactado == NULL) {
        perror("Erro");
    }

    int i;
    fread(&i,sizeof(int),1,compactado);
    static char ext[10];
    fread(&ext,sizeof(char),i,compactado);

    int frequencia[257];
    fread(frequencia,sizeof(int),257,compactado);
    Lista* lista = inicLista();
    preencheLista(lista,frequencia);

    Arv* huffman = geraArv(lista);

    descompacta(compactado,huffman,argv[1],ext);

    liberaArv(huffman);
    liberaLista(lista);
    fclose(compactado);

    return 0;
}