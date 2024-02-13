CC=clang

DEBUG_CFLAGS= -g -march=native -Wall -Wextra
LD_FLAGS=-lm

SRC=$(wildcard ./*.c) $(wildcard ./**/*.c)
OBJ=./obj
LIB=./
BIN=./bin

all: test

debug: $(SRC)
	$(CC) -I $(LIB) $(DEBUG_CFLAGS) -c $(SRC)
	mv *.o $(OBJ)

test: debug
	$(CC) $(LD_FLAGS) $(OBJ)/*.o -o $(BIN)/test

clean:
	rm $(OBJ)/*.o
