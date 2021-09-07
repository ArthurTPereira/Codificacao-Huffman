
PROJ_NAME=Huffman

C_SOURCE=$(wildcard *.c)

H_SOURCE=$(wildcard *.h)

OBJ=$(C_SOURCE:.c=.o)

CC=gcc

CC_FLAGS=-c


all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ -lm
	rm -rf *.o

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H.SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

run:
	./$(PROJ_NAME)

clean:
	rm -rf *.o *~ $(PROJ_NAME)