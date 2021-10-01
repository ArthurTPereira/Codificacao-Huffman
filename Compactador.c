#include <stdio.h>
#include "frequencia.h"
#include "arvore.h"
#include "dicionario.h"
#include "operacoes.h"

int main(int argc, char* argv[]) {

    //Abre o arquivo a ser compactado
    FILE* txt = fopen(argv[1],"rb");
    if (txt == NULL) {
        perror("Erro");
    }

    //Faz a tabela de frequência
    int* vet = preencheFrequencia(txt);
    Lista* lista = inicLista();

    //Preenche a lista encadeada com a tabela de frequência
    preencheLista(lista,vet);

    //Gera a árvore de Huffman a partir da lista encadeada
    Arv* huffman = geraArv(lista);

    //Aloca um dicionário com a quantidade de colunas do tamanho da altura da árvore
    char** dicionario = alocaDicionario(retornaAltura(huffman));

    //Preenche o dicionário
    criaDicionario(dicionario,huffman,"",retornaAltura(huffman));

    //Compacta o arquivo
    compacta(dicionario,txt,argv[1],vet);

    //Libera a memória
    fclose(txt);
    liberaArv(huffman);
    liberaTabela(vet);
    liberaLista(lista);
    liberaDicionario(dicionario);

    return 0;
}