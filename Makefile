OUT=./build
SRC=./src
CC=g++
WF=-Wall -Wextra -Wpedantic -Werror -Wimplicit-fallthrough -Wsign-conversion
FF=clang-format -i -style=Google
CF=$(WF) -std=c++23 -g

graph.o: $(SRC)/Graph.hpp $(SRC)/Graph.cpp
	$(FF) $^ && $(CC) $(CF) -c $^

between.o: $(SRC)/between.hpp $(SRC)/between.cpp
	$(FF) $^ && $(CC) $(CF) -c $^

clean:
	rm -rf $(OUT)/*
