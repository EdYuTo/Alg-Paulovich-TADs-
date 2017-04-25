all: clean arvorebinaria.o item.o heapd.o huffman.o main.o
	@gcc item.o heapd.o arvorebinaria.o huffman.o main.o -o main -Wall -g -lm

arvorebinaria.o:
	@gcc -c arvorebinaria.c

huffman.o:
	@gcc -c huffman.c

item.o:
	@gcc -c item.c

heapd.o:
	@gcc -c heapd.c

main.o:
	@gcc -c main.c

run:
	@valgrind ./main <1.in

clean:
	@find -name '*.o' | xargs rm -rf {}
	@find -name '*~' | xargs rm -rf {}

zip:
	zip -r main *.c *.h Makefile

