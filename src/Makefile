CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=
INPUT=

.PHONY: clean all

all: main
	./main

main: main.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)