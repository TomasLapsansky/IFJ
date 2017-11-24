CC=gcc
CFLAGS=-std=c99 -Wall -W -Wextra -pedantic -ggdb
RM=rm -f

all: test_syn1 test_syn2 test_syn3

test_syn1: main1.o scanner.o parser.o ts.o tstack.o
	$(CC) $(CFLAGS) scanner.o code1_test/main.o parser.o ts.o tstack.o -o code1_test/$@

test_syn2: main2.o scanner.o parser.o
	$(CC) $(CFLAGS) scanner.o code2_test/main.o parser.o -o code2_test/$@

test_syn3: main3.o scanner.o parser.o
	$(CC) $(CFLAGS) scanner.o code3_test/main.o parser.o -o code3_test/$@

main1.o: code1_test/main.c ts.o tstack.o parser.o
	$(CC) $(CFLAGS) -c code1_test/main.c -o code1_test/main.o

main2.o: code2_test/main.c
	$(CC) $(CFLAGS) -c code2_test/main.c -o code2_test/main.o

main3.o: code3_test/main.c
	$(CC) $(CFLAGS) -c code3_test/main.c -o code3_test/main.o

scanner.o: ../scanner.c
	$(CC) $(CFLAGS) -c ../scanner.c -o $@

parser.o: ../parser.c ../parser.h ts.o tstack.o
	$(CC) $(CFLAGS) -c ../parser.c -o $parser.o

ts.o: ../ts.c
	$(CC) $(CFLAGS) -c ../ts.c -o $@

tstack.o: ../tstack.c ../tstack.h scanner.o ts.o
	$(CC) $(CFLAGS) -c ../tstack.c ../tstack.h -o tstack.o

clean:
	$(RM) *.o
	$(RM) */*.o