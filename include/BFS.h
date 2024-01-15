#pragma once

#include "Graph.h"
#include "Path.h"

class BreadthFirstSearch {
 public:
  Path operator()(const Graph&, const Vertex);
};

using BFS = BreadthFirstSearch;
