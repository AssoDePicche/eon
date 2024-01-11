#ifndef DFS_H
#define DFS_H

#include <Graph.h>
#include <Path.h>

class DepthFirstSearch {
 public:
  Path operator()(const Graph, const Vertex);
};

using DFS = DepthFirstSearch;

#endif
