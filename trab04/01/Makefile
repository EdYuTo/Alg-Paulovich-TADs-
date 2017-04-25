all: clean item.o heapd.o main.o
	@gcc item.o heapd.o main.o -o main -Wall -g -lm

item.o:
	@gcc -c item.c

heapd.o:
	@gcc -c heapd.c

main.o:
	@gcc -c main.c

run:
	@./main

clean:
	@find -name '*.o' | xargs rm -rf {}
	@find -name '*~' | xargs rm -rf {}

zip:
	zip -r main *.c *.h Makefile

