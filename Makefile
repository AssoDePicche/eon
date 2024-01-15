INCLUDE=./include
SOURCE=./src

CC = g++
CFLAGS = -I $(INCLUDE) -std=c++23 -Wall -Wextra -Wpedantic -Werror -Wcast-align -Wimplicit-fallthrough -Wsign-conversion -g -O3

SRCS = $(wildcard $(SOURCE)/*.cpp)

OBJ = $(patsubst $(SOURCE)/.cpp, %.o, $(SRCS));

App: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

format:
	clang-format -i --style=Google --sort-includes --verbose $(INCLUDE)/* $(SOURCE)/*

clean:
	rm App

.PHONY: format

.PHONY: clean
