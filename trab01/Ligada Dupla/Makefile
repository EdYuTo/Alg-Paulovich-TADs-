all: clean item.o lista.o main.o 
	@gcc item.o lista.o main.o -o main

item.o:
	@gcc -c item.c

lista.o:
	@gcc -c lista.c

main.o:
	@gcc -c main.c

run:
	@./main

clean:
	@find -name '*.o' | xargs rm -rf {}
	@find -name '*~' | xargs rm -rf {}

zip:
	zip -r main *.c *.h Makefile
