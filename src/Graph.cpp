#include "Graph.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <sstream>

using std::ifstream;
using std::nullopt;
using std::stringstream;

Weight max_weight(void) { return std::numeric_limits<Weight>::max(); }

Graph::Graph(const uint32_t vertices) : _vertices(vertices) {
  matrix = vector(_vertices, vector(_vertices, 0.0f));

  for (uint32_t i = 0; i < _vertices; ++i) {
    for (uint32_t j = 0; j < _vertices; ++j) {
      if (i == j) {
        matrix[i][j] = 1.0f;
      }
    }
  }
}

void Graph::add_edge(const Vertex origin, const Vertex destination,
                     const Weight weight) {
  matrix[origin][destination] = weight;
}

uint32_t Graph::vertices(void) const { return _vertices; }

vector<Weight> &Graph::operator[](const uint32_t row) { return matrix[row]; }

const vector<Weight> &Graph::operator[](const uint32_t row) const {
  return matrix[row];
}

ostream &operator<<(ostream &out, const Graph &graph) {
  for (uint32_t i = 0; i < graph.vertices(); ++i) {
    for (uint32_t j = 0; j < graph.vertices(); ++j) {
      out << graph[i][j] << ' ';
    }

    out << '\n';
  }

  return out;
}

optional<Graph> Graph::make(const string filename) {
  ifstream file;

  file.open(filename);

  if (!file.is_open()) {
    return nullopt;
  }

  string line;

  getline(file, line);

  const auto vertices = static_cast<uint32_t>(atoi(line.c_str()));

  Graph graph(vertices);

  uint32_t origin = 0;

  while (getline(file, line)) {
    stringstream stream(line);

    string buffer;

    for (uint32_t destination = 0; destination < vertices; ++destination) {
      getline(stream, buffer, ',');

      const auto weight = atof(buffer.c_str());

      if (weight != 0.0f) {
        graph.add_edge(Vertex(origin), Vertex(destination), weight);
      }
    }

    origin++;
  }

  return graph;
}
