CC=gcc
CFLAGS=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
LDFLAGS=-Wl,--wrap=free
LIBS=-lcmocka

all: test_list

test_list: test_list.o list.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

test_list.o: test_list.c
	$(CC) $(CFLAGS) -c $<

list.o: list.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fv test_list *.o

.PHONY: test
test: test_list
	@echo
	@echo "Link step:"
	$(CC) $(LDFLAGS) -o test_list test_list.o list.o $(LIBS)
	@echo
	./test_list