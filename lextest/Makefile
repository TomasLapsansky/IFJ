CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic
RM=rm -f

test: main.o scanner.o parser.o
	$(CC) $(CFLAGS) scanner.o main.o parser.o -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $@

scanner.o: ../scanner.c
	$(CC) $(CFLAGS) -c ../scanner.c -o $@

parser.o: ../parser.c ../parser.h
	$(CC) $(CFLAGS) -c ../parser.c -o $@

clean:
	$(RM) *.o