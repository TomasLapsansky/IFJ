CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic -ggdb
RM=rm -f


all: main.o scanner.o parser.o symtable.o psa.o psalist.o tstack.o gener_fce.o
	$(CC) $(CFLAGS) scanner.o main.o parser.o symtable.o psa.o psalist.o tstack.o gener_fce.o -o prg

parser.o: parser.c parser.h scanner.o psa.o psalist.o
	$(CC) $(CFLAGS) -c parser.c -o $@

gener_fce.o: gener_fce.c
	$(CC) $(CFLAGS) -c gener_fce.c -o $@

main.o: main.c scanner.h parser.h
	$(CC) $(CFLAGS) -c main.c -o $@

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c -o $@

symtable.o: symtable.c symtable.h
	$(CC) $(CFLAGS) -c symtable.c -o $@

psalist.o: psalist.c psalist.h
	$(CC) $(CFLAGS) -c psalist.c -o $@

psa.o: psa.c psa.h scanner.o psalist.o
	$(CC) $(CFLAGS) -c psa.c -o $@

tstack.o: tstack.c tstack.h
	$(CC) $(CFLAGS) -c tstack.c -o $@

test: all
	cd tests; bash test.sh

clean:
	$(RM) *.o