all: clean item.o mtesparsa.o main.o
	@gcc item.o mtesparsa.o main.o -o main -Wall -g

item.o:
	@gcc -c item.c

mtesparsa.o:
	@gcc -c mtesparsa.c

main.o:
	@gcc -c main.c

run:
	@./main

clean:
	@find -name '*.o' | xargs rm -rf {}
	@find -name '*~' | xargs rm -rf {}

zip:
	zip -r main *.c *.h Makefile
