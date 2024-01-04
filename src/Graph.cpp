#include "Graph.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_set>

using std::endl;
using std::greater;
using std::ifstream;
using std::nullopt;
using std::numeric_limits;
using std::priority_queue;
using std::queue;
using std::reverse;
using std::sort;
using std::stack;
using std::stringstream;
using std::unordered_set;

Edge::Edge(const Vertex origin, const Vertex destination, const Weight weight)
    : origin(origin), destination(destination), weight(weight) {}

Weight Edge::max_weight(void) { return numeric_limits<Weight>::max(); }

bool operator<(const Edge &uv, const Edge &uw) { return uv.weight < uw.weight; }

bool operator>(const Edge &uv, const Edge &uw) { return !(uv < uw); }

bool operator==(const Edge &uv, const Edge &vu) {
  return !(uv < vu) && !(uv > vu);
}

WeightedVertex::WeightedVertex(const Vertex vertex, const Weight weight)
    : vertex(vertex), weight(weight){};

bool operator<(const WeightedVertex &u, const WeightedVertex &v) {
  return u.weight < v.weight;
}

bool operator>(const WeightedVertex &u, const WeightedVertex &v) {
  return !(u < v);
}

Graph::Graph(const uint32_t number_of_vertices)
    : number_of_vertices(number_of_vertices) {
  matrix = vector(number_of_vertices, vector<Weight>(number_of_vertices, 0));
}

void Graph::add_edge(const Vertex origin, const Vertex destination,
                     const Weight weight) {
  vertices.insert(origin);

  vertices.insert(destination);

  matrix[origin][destination] = weight;

  edges.push_back(Edge(origin, destination, weight));
}

set<Vertex> Graph::neighbors_of(const Vertex vertex) {
  set<Vertex> neighbors;

  for (auto iterator = matrix[vertex].begin(); iterator < matrix[vertex].end();
       ++iterator) {
    if (*iterator != 0) {
      neighbors.insert(distance(matrix[vertex].begin(), iterator));
    }
  }

  return neighbors;
}

vector<Edge> Graph::get_edges(void) { return edges; }

set<Vertex> Graph::get_vertices(void) { return vertices; }

Path Graph::a_star_search(const Vertex origin, const Vertex destination) {
  vector<Vertex> came_from(number_of_vertices, Edge::max_weight());

  vector<Weight> g_score(number_of_vertices, Edge::max_weight());

  vector<Weight> f_score(number_of_vertices, Edge::max_weight());

  priority_queue<WeightedVertex, vector<WeightedVertex>, greater<>> open_set;

  unordered_set<Vertex> closed_set;

  const auto heuristic = [](Vertex u, Vertex v) {
    return static_cast<Weight>(v - u);
  };

  g_score[origin] = 0;

  f_score[origin] = heuristic(origin, destination);

  open_set.push(WeightedVertex(origin, f_score[origin]));

  while (!open_set.empty()) {
    auto vertex = open_set.top().vertex;

    open_set.pop();

    if (vertex == destination) {
      Path path;

      while (vertex != Edge::max_weight()) {
        path.push_back(vertex);

        vertex = came_from[vertex];
      }

      path.push_back(origin);

      return path;
    }

    closed_set.insert(vertex);

    for (const auto &neighbor : neighbors_of(vertex)) {
      if (closed_set.find(neighbor) != closed_set.end()) {
        continue;
      }

      const auto x = g_score[vertex] + matrix[vertex][neighbor];

      if (x < g_score[neighbor]) {
        came_from[neighbor] = vertex;

        g_score[neighbor] = x;

        f_score[neighbor] =
            g_score[neighbor] +
            heuristic(static_cast<Vertex>(neighbor), destination);

        open_set.push(WeightedVertex(neighbor, f_score[neighbor]));
      }
    }
  }

  return {};
}

Path Graph::breadth_first_search(const Vertex origin) {
  vector<bool> visited(number_of_vertices, false);

  queue<Vertex> queue;

  queue.push(origin);

  visited[origin] = true;

  Path path;

  while (!queue.empty()) {
    auto vertex = queue.front();

    queue.pop();

    path.push_back(vertex);

    for (const auto &neighbor : neighbors_of(vertex)) {
      if (!visited[neighbor]) {
        queue.push(neighbor);

        visited[neighbor] = true;
      }
    }
  }

  return path;
}

Path Graph::depth_first_search(const Vertex origin) {
  vector<bool> visited(number_of_vertices, false);

  stack<Vertex> stack;

  stack.push(origin);

  visited[origin] = true;

  Path path;

  while (!stack.empty()) {
    auto vertex = stack.top();

    stack.pop();

    path.push_back(vertex);

    for (const auto &neighbors : neighbors_of(vertex)) {
      if (!visited[neighbors]) {
        stack.push(neighbors);

        visited[neighbors] = true;
      }
    }
  }

  sort(path.begin(), path.end());

  return path;
}

Path Graph::dijkstra_shortest_path(const Vertex origin,
                                   const Vertex destination) {
  if (origin == destination) {
    return {};
  }

  vector<bool> visited(number_of_vertices, false);

  vector<Weight> weights(number_of_vertices, Edge::max_weight());

  vector<int> predecessors(number_of_vertices, -1);

  weights[origin] = 0;

  for (uint32_t iteration = 0; iteration < number_of_vertices - 1;
       ++iteration) {
    Vertex nearest_vertex = 0;

    auto minimum_weight = Edge::max_weight();

    for (Vertex vertex = 0; vertex < number_of_vertices; ++vertex) {
      const auto visited_vertex = visited[vertex];

      const auto weight = weights[vertex];

      if (!visited_vertex && weight <= minimum_weight) {
        nearest_vertex = vertex;

        minimum_weight = weight;
      }
    }

    visited[nearest_vertex] = true;

    for (Vertex adjacent_vertex = 0; adjacent_vertex < number_of_vertices;
         ++adjacent_vertex) {
      const auto edge_weight = matrix[nearest_vertex][adjacent_vertex];

      const auto weight = weights[nearest_vertex];

      const auto new_weight = weight + edge_weight;

      const auto visited_vertex = visited[adjacent_vertex];

      const auto minimum_weight = weights[adjacent_vertex];

      if (edge_weight != 0 && !visited_vertex && weight != Edge::max_weight() &&
          new_weight < minimum_weight) {
        weights[adjacent_vertex] = new_weight;

        predecessors[adjacent_vertex] = static_cast<int>(nearest_vertex);
      }
    }
  }

  Path path;

  auto current_vertex = static_cast<int>(destination);

  while (current_vertex != -1 &&
         static_cast<Vertex>(current_vertex) != origin) {
    path.push_back(static_cast<Vertex>(current_vertex));

    current_vertex = predecessors[static_cast<uint32_t>(current_vertex)];
  }

  if (static_cast<Vertex>(current_vertex) == origin) {
    path.push_back(origin);
  } else {
    path.clear();
  }

  reverse(path.begin(), path.end());

  return path;
}

ostream &operator<<(ostream &out, const Graph &graph) {
  out << "  ";

  for (const auto &vertex : graph.vertices) {
    out << vertex << ' ';
  }

  out << endl;

  auto iterator = graph.vertices.begin();

  for (const auto &row : graph.matrix) {
    out << *iterator << ' ';

    iterator++;

    for (const auto &column : row) {
      out << column << ' ';
    }

    out << endl;
  }

  return out;
}

optional<Graph> GraphFactory::make(const string filename, const Source source) {
  ifstream file;

  file.open(filename);

  if (!file.is_open()) {
    return nullopt;
  }

  string line;

  getline(file, line);

  const auto number_of_vertices = static_cast<uint32_t>(atoi(line.c_str()));

  Graph graph(number_of_vertices);

  Vertex origin = 0;

  while (getline(file, line)) {
    stringstream stream(line);

    string buffer;

    if (source == Source::EDGE_LIST) {
      getline(stream, buffer, ',');

      const auto origin = static_cast<Vertex>(atoi(buffer.c_str()));

      getline(stream, buffer, ',');

      const auto destination = static_cast<Vertex>(atoi(buffer.c_str()));

      getline(stream, buffer, ',');

      const auto weight = atof(buffer.c_str());

      graph.add_edge(origin, destination, weight);

      continue;
    }

    for (Vertex destination = 0; destination < number_of_vertices;
         ++destination) {
      getline(stream, buffer, ',');

      const auto weight = atof(buffer.c_str());

      if (weight != 0) {
        graph.add_edge(origin, destination, weight);
      }
    }

    origin++;
  }

  return graph;
}
