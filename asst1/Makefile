all: mymalloc.o memgrind.c
	gcc -o memgrind mymalloc.o memgrind.c -g

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c -g

clean:
	rm -f *.o
	rm -f memgrind
