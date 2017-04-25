all: clean arvorebinaria.o item.o heapdinamica.o huffman.o main.o
	@gcc item.o heapdinamica.o arvorebinaria.o huffman.o main.o -o main -Wall -g -lm

arvorebinaria.o:
	@gcc -c arvorebinaria.c

huffman.o:
	@gcc -c huffman.c

item.o:
	@gcc -c item.c

heapdinamica.o:
	@gcc -c heapdinamica.c

main.o:
	@gcc -c main.c

run:
	@./main

clean:
	@find -name '*.o' | xargs rm -rf {}
	@find -name '*~' | xargs rm -rf {}

zip:
	zip -r main *.c *.h Makefile

