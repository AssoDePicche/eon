OUT=./build
SRC=./src
APP=$(SRC)/App.cpp
CC=g++
WF=-Wall -Wextra -Wpedantic -Werror -Wimplicit-fallthrough -Wsign-conversion
FF=clang-format -i -style=Google
CF=$(WF) -std=c++23 -g -I $(SRC)/graph -I $(SRC)/search

all: weight.o matrix.o dsp.o edge.o path.o bfs.o dfs.o graph.o $(APP)
	$(FF) $(APP) && $(CC) $(CF) -o App.o $^ && mv *.o $(OUT) && rm $(SRC)/*/*.*.gch

bfs.o: $(SRC)/search/BFS.*
	$(FF) $^ && $(CC) $(CF) -c $^

dfs.o: $(SRC)/search/DFS.*
	$(FF) $^ && $(CC) $(CF) -c $^

dsp.o: $(SRC)/search/DSP.*
	$(FF) $^ && $(CC) $(CF) -c $^

ath.o: $(SRC)/graph/Path.*
	$(FF) $^ && $(CC) $(CF) -c $^

vertex.o: $(SRC)/graph/Vertex.*
	$(FF) $^ && $(CC) $(CF) -c $^

graph.o: $(SRC)/graph/Graph.*
	$(FF) $^ && $(CC) $(CF) -c $^

matrix.o: $(SRC)/graph/Matrix.*
	$(FF) $^ && $(CC) $(CF) -c $^

edge.o: $(SRC)/graph/Edge.*
	$(FF) $^ && $(CC) $(CF) -c $^

weight.o: $(SRC)/graph/Weight.*
	$(FF) $^ && $(CC) $(CF) -c $^

between.o: $(SRC)/graph/between.*
	$(FF) $^ && $(CC) $(CF) -c $^

clean:
	rm -rf $(OUT)/* && rm $(SRC)/*/*.*.gch
