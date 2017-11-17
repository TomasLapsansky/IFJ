CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic
RM=rm -f

prg: mainclean main.o scanner.o
	$(CC) scanner.o main.o -o $@

main.o: main.c scanner.h
	$(CC) $(CFLAGS) -c main.c -o $@

lextest: mainclean main.o scanner.o
	$(CC) $(CFLAGS) main.o scanner.o -o lextest

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c -o $@

test.o: lextest/main.c
	$(CC) $(CFLAGS) -c lextest/main.c main.o

mainclean:
	$(RM) main.o

clean:
	$(RM) *.o