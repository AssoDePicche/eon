#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <set>
#include <vector>

#include "Edge.h"
#include "Matrix.h"
#include "Vertex.h"

using std::optional;
using std::ostream;
using std::set;
using std::string;
using std::uint32_t;
using std::vector;

class Graph {
 public:
  Graph(void) = default;

  Graph(const uint32_t);

  void add_edge(const Vertex, const Vertex, const Weight = 0.0f);

  set<Vertex> neighbors_of(const Vertex) const;

  vector<Edge> get_edges(void) const;

  set<Vertex> get_vertices(void) const;

  uint32_t get_number_of_vertices(void) const;

  vector<Weight> &operator[](const uint32_t);

  const vector<Weight> &operator[](const uint32_t) const;

  friend ostream &operator<<(ostream &, const Graph &);

  static optional<Graph> make(const string);

 private:
  vector<Edge> edges;
  uint32_t number_of_vertices;
  Matrix matrix;
  set<Vertex> vertices;
};
