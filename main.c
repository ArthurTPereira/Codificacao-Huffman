#include <stdio.h>
#include <stdlib.h>
#include "frequencia.h"
#include "arvore.h"

int main() {
	
    FILE* txt = fopen("exemplo.txt","r");
    if (txt == NULL) {
        perror("Erro");
        exit(1);
    }

	int* vet = preencheFrequencia(txt);
    fclose(txt);


    /*
    printf("-------- Tabela de frequência --------\n");
    imprimeTabelaFrequencia(vet);
    printf("\n");
    */

    Lista* lista = inicLista();
    preencheLista(lista,vet);

    /*
    printf("-------- Lista Ordenada --------\n");
    imprimeLista(lista);
    */

    Arv* huffman = geraArv(lista);
    
    //imprimeArv(huffman);

    char** dic = alocaDicionario(retornaAltura(huffman));
    criaDicionario(dic,huffman,"",retornaAltura(huffman));
    
    imprimeDicionario(dic);

    liberaArv(huffman);
    liberaLista(lista);
    liberaTabela(vet);
    liberaDicionario(dic);
    
    return 0;
}
