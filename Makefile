CC=clang

DEBUG_CFLAGS= -g -march=native -Wall -Wextra
RELEASE_CFLAGS= -O3 -march=native -Wall -Wextra
LD_FLAGS=-lm

SRC=$(wildcard ./*.c) $(wildcard ./src/*.c) $(wildcard ./src/**/*.c)
OBJ=./obj
LIB=./
BIN=./bin

all: test

debug: $(SRC)
	$(CC) -I $(LIB) $(DEBUG_CFLAGS) -c $(SRC)
	mv *.o $(OBJ)

optimized: $(SRC)
	$(CC) -I $(LIB) $(RELEASE_CFLAGS) -c $(SRC)
	mv *.o $(OBJ)

test: debug
	$(CC) $(LD_FLAGS) $(OBJ)/*.o -o $(BIN)/test

release: optimized
	$(CC) $(LD_FLAGS) $(OBJ)/*.o -o $(BIN)/test

clean:
	rm $(OBJ)/*.o
