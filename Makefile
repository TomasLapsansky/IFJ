CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic
RM=rm -f

prg: main.o scanner.o parser.o
	$(CC) $(CFLAGS) scanner.o main.o parser.o -o $@

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c -o $@

main.o: main.c scanner.h parser.h
	$(CC) $(CFLAGS) -c main.c -o $@

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c -o $@

clean:
	$(RM) *.o
