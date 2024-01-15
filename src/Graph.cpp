#include "Graph.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

using std::ifstream;
using std::nullopt;
using std::stringstream;

Graph::Graph(const uint32_t number_of_vertices)
    : number_of_vertices(number_of_vertices) {
  matrix = Matrix::make_identity_matrix(number_of_vertices);
}

void Graph::add_edge(const Vertex origin, const Vertex destination,
                     const Weight weight) {
  vertices.insert(origin);

  vertices.insert(destination);

  matrix[origin][destination] = weight;

  edges.push_back(Edge(origin, destination, weight));
}

set<Vertex> Graph::neighbors_of(const Vertex vertex) const {
  set<Vertex> neighbors;

  for (auto iterator = matrix[vertex].begin(); iterator < matrix[vertex].end();
       ++iterator) {
    if (*iterator != 0.0f) {
      neighbors.insert(distance(matrix[vertex].begin(), iterator));
    }
  }

  return neighbors;
}

vector<Edge> Graph::get_edges(void) const { return edges; }

set<Vertex> Graph::get_vertices(void) const { return vertices; }

uint32_t Graph::get_number_of_vertices(void) const {
  return number_of_vertices;
}

vector<Weight> &Graph::operator[](const uint32_t row) { return matrix[row]; }

const vector<Weight> &Graph::operator[](const uint32_t row) const {
  return matrix[row];
}

ostream &operator<<(ostream &out, const Graph &graph) {
  return out << graph.matrix;
}

optional<Graph> Graph::make(const string filename) {
  ifstream file;

  file.open(filename);

  if (!file.is_open()) {
    return nullopt;
  }

  string line;

  getline(file, line);

  const auto number_of_vertices = static_cast<uint32_t>(atoi(line.c_str()));

  Graph graph(number_of_vertices);

  uint32_t origin = 0;

  while (getline(file, line)) {
    stringstream stream(line);

    string buffer;

    for (uint32_t destination = 0; destination < number_of_vertices;
         ++destination) {
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
