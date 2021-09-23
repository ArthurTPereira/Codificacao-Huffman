#include <stdio.h>
#include "frequencia.h"
#include "arvore.h"

int main(int argc, char* argv[]) {

    FILE* txt = fopen(argv[1],"rb");
    if (txt == NULL) {
        perror("Erro");
    }

    int* vet = preencheFrequencia(txt);
    Lista* lista = inicLista();
    preencheLista(lista,vet);

    Arv* huffman = geraArv(lista);

    char** dicionario = alocaDicionario(retornaAltura(huffman));
    criaDicionario(dicionario,huffman,"",retornaAltura(huffman));

    compacta(dicionario,txt,argv[1],vet);

    fclose(txt);
    liberaArv(huffman);
    liberaTabela(vet);
    liberaLista(lista);
    liberaDicionario(dicionario);

    return 0;
}