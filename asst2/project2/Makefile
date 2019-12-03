all: 
	$(error Use make thread or make proc)

thread: multitest_thread.o multitest.h searchtest.c
	gcc -o search multitest_thread.o searchtest.c -lpthread -lm -w

proc: multitest_proc.o multitest.h searchtest.c
	gcc -o search multitest_proc.o searchtest.c -lm -w

multitest_thread.o: multitest_thread.c
	gcc -c multitest_thread.c -lpthread

multitest_proc.o: multitest_proc.c
	gcc -c multitest_proc.c

clean:
	rm -f *.o
	rm -f search


