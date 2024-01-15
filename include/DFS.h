#pragma once

#include "Graph.h"
#include "Path.h"

class DepthFirstSearch {
 public:
  Path operator()(const Graph&, const Vertex);
};

using DFS = DepthFirstSearch;
