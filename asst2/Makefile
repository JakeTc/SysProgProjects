proc: multitest_proc.o searchtest.c
	gcc -o searchtest multitest_proc.o searchtest.c -g

thread: multitest_thread.o searchtest.c
	gcc -o searchtest -lpthread -lm multitest_thread.o searchtest.c -g

multitest_proc.o: multitest_proc.c multitest.h
	gcc -c multitest_proc.c -g

multitest_thread.o: multitest_thread.c multitest.h
	gcc -c multitest_thread.c -g

clean:
	rm -f *.o
	rm -f searchtest
