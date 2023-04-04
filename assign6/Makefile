.PHONY: all clean run

all: exec_env execd_pgm

exec_env: exec_env.c
	gcc -o exec_env exec_env.c

execd_pgm: execd_pgm.c
	gcc -o execd_pgm execd_pgm.c

clean:
	rm -f exec_env execd_pgm

run:
	./exec_env ./execd_pgm EXECD_PGM_NAME=assign6
