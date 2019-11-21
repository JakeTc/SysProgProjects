proc: multitest_proc.o searchtest.c
	gcc -o searchtest multitest_proc.o searchtest.c -g

thread: multitest_thread.o searchtest.c
	gcc -o searchtest multitest_thread.o searchtest.c -g

multitest_proc.o: multitest_proc.c multitest.h
	gcc -c multitest_proc.c -g

clean:
	rm -f *.o
	rm -f searchtest
