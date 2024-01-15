#pragma once

#include "Graph.h"
#include "Path.h"

class DijkstraShortestPath {
 public:
  Path operator()(const Graph&, const Vertex, const Vertex);
};

using DSP = DijkstraShortestPath;
