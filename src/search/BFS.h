#ifndef BFS_H
#define BFS_H

#include <Graph.h>
#include <Path.h>

class BreadthFirstSearch {
 public:
  Path operator()(const Graph, const Vertex);
};

using BFS = BreadthFirstSearch;

#endif
