
PROJ_NAME=Huffman

C_SOURCE=$(wildcard *.c)

H_SOURCE=$(wildcard *.h)

OBJ=$(C_SOURCE:.c=.o)

CC=gcc

CC_FLAGS=-c


all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) arvore.c bitmap.c Compactador.c frequencia.c -o Compacta
	$(CC) arvore.c bitmap.c Descompactador.c frequencia.c -o Descompacta
	rm -rf *.o

clean:
	rm -rf *.o *~ Compacta Descompacta *.comp