CC       = gcc
CFLAGS   = -g -Wall -Wextra
EXECNAME = test1
FILE1    = pthread_testing.c
FILE2    = implementation.c


test1 :
	$(CC) $(CFLAGS) -o $(EXECNAME) $(FILE1) $(FILE2)

clean :
	-rm -f *.o *.core test1
