#include <stdio.h>
#include "frequencia.h"
#include "arvore.h"

int main(int argc, char* argv[]) {
    FILE* compactado = fopen(argv[1],"rb");
    if (compactado == NULL) {
        perror("Erro");
    }

    int frequencia[256];
    fread(frequencia,sizeof(int),256,compactado);
    Lista* lista = inicLista();
    preencheLista(lista,frequencia);

    Arv* huffman = geraArv(lista);

    descompacta(compactado,huffman,argv[1]);

    liberaArv(huffman);
    liberaLista(lista);
    fclose(compactado);

    return 0;
}