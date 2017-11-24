CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic -ggdb
RM=rm -f

prog: main.o parser.o scanner.o ts.o tstack.o
	$(CC) $(CFLAGS) main.o parser.o scanner.o ts.o tstack.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c -o parser.o

scanner.o: scanner.c
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o

ts.o: ts.c
	$(CC) $(CFLAGS) -c ts.c -o ts.o

tstack.o: tstack.c
	$(CC) $(CFLAGS) -c tstack.c -o tstack.o

clean:
	$(RM) *.o prog