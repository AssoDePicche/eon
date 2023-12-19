#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <vector>

using std::endl;
using std::ifstream;
using std::make_unique;
using std::numeric_limits;
using std::ostream;
using std::pair;
using std::priority_queue;
using std::queue;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::vector;

template <typename T>
class Graph {
 public:
  Graph() = default;

  Graph(const uint32_t vertices) {
    this->vertices = vertices;

    adjacency_matrix.resize(vertices);

    visited_nodes.resize(vertices);

    visited_nodes.assign(vertices, false);
  }

  void addEdge(const uint32_t source, const uint32_t destination,
               float weight = 1.0) {
    if (source >= vertices || destination >= vertices || weight < 0) {
      return;
    }

    adjacency_matrix[source].push_back({static_cast<T>(destination), weight});

    adjacency_matrix[destination].push_back({static_cast<T>(source), weight});
  }

  vector<uint32_t> breadth_first_search(const uint32_t source) {
    if (source >= vertices) {
      return {};
    }

    visited_nodes.assign(vertices, false);

    queue<T> queue;

    visited_nodes[source] = true;

    queue.push(static_cast<T>(source));

    vector<uint32_t> nodes;

    while (!queue.empty()) {
      uint32_t node = static_cast<uint32_t>(queue.front());

      nodes.push_back(node);

      queue.pop();

      for (const auto &adjacent_node : adjacency_matrix[node]) {
        if (!visited_nodes[static_cast<uint32_t>(adjacent_node.first)]) {
          visited_nodes[static_cast<uint32_t>(adjacent_node.first)] = true;

          queue.push(adjacent_node.first);
        }
      }
    }

    visited_nodes.assign(vertices, false);

    return nodes;
  }

  vector<uint32_t> depth_first_search(const uint32_t source) {
    if (source >= vertices) {
      return {};
    }

    static vector<uint32_t> nodes;

    visited_nodes[source] = true;

    nodes.push_back(source);

    for (const auto &node : adjacency_matrix[source]) {
      if (!visited_nodes[static_cast<uint32_t>(node.first)]) {
        depth_first_search(static_cast<uint32_t>(node.first));
      }
    }

    return nodes;
  }

  vector<float> dijkstras_shortest_paths(const uint32_t source) {
    if (source >= vertices) {
      return {};
    }

    priority_queue<pair<T, float>> queue;

    vector<float> distances(vertices, numeric_limits<float>::max());

    distances[source] = 0;

    queue.push({source, 0.0});

    while (!queue.empty()) {
      uint32_t v = static_cast<uint32_t>(queue.top().first);

      float weight = -queue.top().second;

      queue.pop();

      if (weight != distances[v]) {
        continue;
      }

      for (const auto &edge : adjacency_matrix[v]) {
        T node = edge.first;

        float weight = edge.second;

        if (distances[static_cast<uint32_t>(node)] > distances[v] + weight) {
          distances[static_cast<uint32_t>(node)] = distances[v] + weight;

          queue.push({node, -distances[static_cast<uint32_t>(node)]});
        }
      }
    }

    return distances;
  }

  static unique_ptr<Graph<T>> make(const string filename) {
    ifstream file;

    file.open(filename);

    if (!file.is_open()) {
      return NULL;
    }

    string line;

    getline(file, line);

    uint32_t vertices = static_cast<uint32_t>(atoi(line.c_str()));

    unique_ptr<Graph<T>> graph = make_unique<Graph<T>>(vertices);

    while (getline(file, line)) {
      stringstream stream(line);

      string buffer;

      getline(stream, buffer, ',');

      uint32_t u = static_cast<uint32_t>(atoi(buffer.c_str()));

      getline(stream, buffer, ',');

      uint32_t v = static_cast<uint32_t>(atoi(buffer.c_str()));

      getline(stream, buffer);

      float weight = atof(buffer.c_str());

      graph->addEdge(u, v, weight);
    }

    file.close();

    return graph;
  }

  friend ostream &operator<<(ostream &out, const Graph<T> graph) {
    uint32_t node = 0;

    for (const auto &row : graph.adjacency_matrix) {
      out << node << ": ";

      for (const auto &column : row) {
        out << column.first << ' ';
      }

      ++node;

      out << endl;
    }

    return out;
  }

 private:
  uint32_t vertices = 0;
  vector<vector<pair<T, float>>> adjacency_matrix;
  vector<bool> visited_nodes;
};

#endif
