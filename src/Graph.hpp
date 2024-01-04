#ifndef GRAPH_H
#define GRAPH_H

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

template <typename T>
using Matrix = vector<vector<T>>;
using Vertex = uint32_t;
using Weight = float;
using Path = vector<Vertex>;

struct WeightedVertex {
  Vertex vertex;
  Weight weight;

  WeightedVertex(void) = default;

  WeightedVertex(const Vertex vertex, const Weight weight);
};

bool operator<(const WeightedVertex &u, const WeightedVertex &v);

bool operator>(const WeightedVertex &u, const WeightedVertex &v);

struct Edge {
  Vertex origin;
  Vertex destination;
  Weight weight;

  Edge(void) = default;

  Edge(const Vertex origin, const Vertex destination, const Weight weight);

  static Weight max_weight(void);
};

bool operator<(const Edge &uv, const Edge &uw);

bool operator>(const Edge &uv, const Edge &uw);

bool operator==(const Edge &uv, const Edge &vu);

class Graph {
 public:
  Graph(void) = default;

  Graph(const uint32_t number_of_vertices);

  void add_edge(const Vertex origin, const Vertex destination,
                const Weight weight = 0.0);

  vector<Edge> get_edges(void);

  set<Vertex> neighbors_of(const Vertex vertex);

  set<Vertex> get_vertices(void);

  Path a_star_search(const Vertex origin, const Vertex destination);

  Path breadth_first_search(const Vertex origin);

  Path depth_first_search(const Vertex origin);

  Path dijkstra_shortest_path(const Vertex origin, const Vertex destination);

  friend ostream &operator<<(ostream &out, const Graph &graph);

 private:
  vector<Edge> edges;
  uint32_t number_of_vertices;
  Matrix<Weight> matrix;
  set<Vertex> vertices;
};

enum Source {
  ADJACENCY_LIST,
  EDGE_LIST,
};

class GraphFactory {
 public:
  static optional<Graph> make(const string filename,
                              const Source source = EDGE_LIST);
};

#endif
