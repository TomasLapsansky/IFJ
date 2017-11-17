CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic
RM=rm -f

test_lex: main.o scanner.o
	$(CC) scanner.o main.o -o $@

main.o: main.c scanner.h
	$(CC) $(CFLAGS) -c main.c -o $@

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c -o $@

clean:
	$(RM) *.o