CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic -ggdb
RM=rm -f


prg: main.o scanner.o parser.o ts.o psa.o psalist.o tstack.o
	$(CC) $(CFLAGS) scanner.o main.o parser.o ts.o psa.o psalist.o tstack.o -o $@

parser.o: parser.c parser.h scanner.o psa.o psalist.o
	$(CC) $(CFLAGS) -c parser.c -o $@

main.o: main.c scanner.h parser.h
	$(CC) $(CFLAGS) -c main.c -o $@

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c -o $@

ts.o: ts.c ts.h
	$(CC) $(CFLAGS) -c ts.c -o $@

psalist.o: psalist.c psalist.h
	$(CC) $(CFLAGS) -c psalist.c -o $@

psa.o: psa.c psa.h scanner.o psalist.o
	$(CC) $(CFLAGS) -c psa.c -o $@

tstack.o: tstack.c tstack.h
	$(CC) $(CFLAGS) -c tstack.c -o $@

clean:
	$(RM) *.o