#KRY 2023- proj1
#author: Jakub Komárek (xkomar33)

CFLAGS= -Wall -g

BIN=kry
ZIP=xkomar33.zip
CC=g++ 
RM=rm -f
SRC=main.cpp encrypt.cpp decrypt.cpp break.cpp

.PHONY: all build run pack clean

all: build

build: 
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) 

pack: clean
	zip  $(ZIP) * 

run:
	test -f $(BIN) && ./$(BIN)

valgrind:
	test -f $(BIN) && valgrind ./$(BIN)

clean:
	rm -rf $(BIN) $(ZIP) *.o 
