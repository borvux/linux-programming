#MakeFIle
#Lab03
CC=gcc 
CFLAGS=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra #want to use the gcc compiler #-ggdb -gdwarf-4 -O0 - debugging, -Wall for all errors

malloc_test: malloc.o malloc_test.c 
	$(CC) $(CFlAGS) -o malloc_test malloc.o malloc_test.o

malloc_test.o: malloc_test.c malloc.c malloc.h
	$(CC) $(CFlAGS) -c malloc_test.c

malloc.o: malloc.c malloc.h 
	$(CC) $(CFlAGS) -c malloc.c

clean: #remove all target files
	rm -vf *.o 
