#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <set>
#include <vector>

using std::optional;
using std::ostream;
using std::set;
using std::string;
using std::uint32_t;
using std::vector;

using Vertex = std::uint32_t;
using Weight = float;

Weight max_weight(void);

class Graph {
 public:
  Graph(void) = default;

  Graph(const uint32_t);

  void add_edge(const Vertex, const Vertex, const Weight = 0.0f);

  uint32_t vertices(void) const;

  vector<Weight> &operator[](const uint32_t);

  const vector<Weight> &operator[](const uint32_t) const;

  friend ostream &operator<<(ostream &, const Graph &);

  static optional<Graph> make(const string);

 private:
  uint32_t _vertices;
  vector<vector<Weight>> matrix;
};