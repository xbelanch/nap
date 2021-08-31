CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=`pkg-config --cflags --libs x11`
INPUT=

.PHONY: test

test: main $(INPUT)
	./main $(INPUT)

main:
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
