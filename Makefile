OUT=./build
SRC=./src
CC=g++
WF=-Wall -Wextra -Wpedantic -Werror -Wimplicit-fallthrough -Wsign-conversion
CF=$(WF) -std=c++23 -O3

graph.o:
	$(CC) $(CF) -o $(OUT)/graph $(SRC)/Graph.hpp

clean:
	rm -rf $(OUT)/*
