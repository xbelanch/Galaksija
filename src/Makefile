CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=
INPUT=
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

.PHONY: clean all

all: main
	./main $(INPUT)

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)