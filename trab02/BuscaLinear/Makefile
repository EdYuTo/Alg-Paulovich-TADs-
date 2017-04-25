all: clean item.o functions.o arraylist.o main.o
	@gcc item.o functions.o arraylist.o main.o -o main -Wall -g

item.o:
	@gcc -c item.c

arraylist.o:
	@gcc -c arraylist.c

functions.o:
	@gcc -c functions.c

main.o:
	@gcc -c main.c

run:
	@./main

clean:
	@find -name '*.o' | xargs rm -rf {}
	@find -name '*~' | xargs rm -rf {}

zip:
	zip -r main *.c *.h Makefile

