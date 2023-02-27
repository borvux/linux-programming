CC=gcc
CFLAGS=-Wall -Wextra

all: compare_static compare_dynamic

compare_static: compare.o
	$(CC) -static -o compare_static compare.o

compare_dynamic: compare.o
	$(CC) -o compare_dynamic compare.o

compare.o: compare.c
	$(CC) $(CFLAGS) -c compare.c

clean:
	rm -f compare_static compare_dynamic compare.o

compare:
	@echo "compare_static size: $(shell du -h compare_static | cut -f 1)"
	@echo "compare_dynamic size: $(shell du -h compare_dynamic | cut -f 1)"
