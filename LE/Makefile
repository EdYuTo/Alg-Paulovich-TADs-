all: item.o lista.o main.o
	gcc -g item.o lista.o main.o -o main -Wall

item.o:
	gcc -g -c item.c

lista.o:
	gcc -g -c lista.c

main.o:
	gcc -g -c main.c

run:
	./main

./clean:
	rm *.o main
