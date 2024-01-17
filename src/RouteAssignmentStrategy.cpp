#include <RouteAssignmentStrategy.h>

#include <limits>
#include <queue>
#include <stack>

using std::queue;
using std::stack;

Route::Route(list<Vertex> vertices) : vertices(vertices) {}

list<Vertex>::iterator Route::begin(void) { return vertices.begin(); }

void Route::clear(void) { vertices.clear(); }

Vertex Route::dequeue(void) {
  auto vertex = vertices.front();

  vertices.pop_front();

  return vertex;
}

bool Route::empty(void) const { return vertices.empty(); }

list<Vertex>::iterator Route::end(void) { return vertices.end(); }

void Route::enqueue(const Vertex vertex) { vertices.push_front(vertex); }

Vertex Route::pop(void) {
  auto vertex = vertices.back();

  vertices.pop_back();

  return vertex;
}

void Route::push(const Vertex vertex) { vertices.push_back(vertex); }

void Route::reverse(void) { vertices.reverse(); }

void Route::sort(void) { vertices.sort(); }

Route BreadthFirstSearch::operator()(const Graph &graph, const Vertex origin,
                                     const Vertex destination) const {
  vector<bool> visited(graph.vertices(), false);

  vector<int> parent(graph.vertices(), -1);

  queue<Vertex> queue;

  queue.push(origin);

  visited[origin] = true;

  while (!queue.empty()) {
    const auto current = queue.front();

    queue.pop();

    for (Vertex neighbor = 0; neighbor < graph.vertices(); ++neighbor) {
      if (graph[current][neighbor] != 0.0f && !visited[neighbor]) {
        queue.push(neighbor);

        visited[neighbor] = true;

        parent[neighbor] = static_cast<int>(current);

        if (neighbor == destination) {
          Route route;

          int vertex = static_cast<int>(destination);

          while (vertex != -1) {
            route.push(static_cast<Vertex>(vertex));

            vertex = parent[static_cast<uint32_t>(vertex)];
          }

          route.reverse();

          return route;
        }
      }
    }
  }

  return Route();
}

Route BreadthFirstSearch::operator()(const Graph &graph,
                                     const Vertex origin) const {
  vector<bool> visited(graph.vertices(), false);

  queue<Vertex> queue;

  queue.push(origin);

  visited[origin] = true;

  Route route;

  while (!queue.empty()) {
    const auto vertex = queue.front();

    queue.pop();

    route.push(vertex);

    for (Vertex neighbor = 0; neighbor < graph.vertices(); ++neighbor) {
      if (graph[vertex][neighbor] == 0.0f || visited[neighbor]) {
        continue;
      }

      queue.push(neighbor);

      visited[neighbor] = true;
    }
  }

  return route;
}

Route DepthFirstSearch::operator()(const Graph &graph, const Vertex origin,
                                   const Vertex destination) const {
  vector<bool> visited(graph.vertices(), false);

  vector<int> parent(graph.vertices(), -1);

  stack<Vertex> stack;

  stack.push(origin);

  visited[origin] = true;

  while (!stack.empty()) {
    const auto current = stack.top();

    stack.pop();

    for (Vertex neighbor = 0; neighbor < graph.vertices(); ++neighbor) {
      if (graph[current][neighbor] != 0.0f && !visited[neighbor]) {
        stack.push(neighbor);

        visited[neighbor] = true;

        parent[neighbor] = static_cast<int>(current);

        if (neighbor == destination) {
          Route route;

          int vertex = static_cast<int>(destination);

          while (vertex != -1) {
            route.push(static_cast<Vertex>(vertex));

            vertex = parent[static_cast<uint32_t>(vertex)];
          }

          route.reverse();

          return route;
        }
      }
    }
  }

  return Route();
}

Route DepthFirstSearch::operator()(const Graph &graph,
                                   const Vertex origin) const {
  vector<bool> visited(graph.vertices(), false);

  stack<Vertex> stack;

  stack.push(origin);

  visited[origin] = true;

  Route route;

  while (!stack.empty()) {
    const auto vertex = stack.top();

    stack.pop();

    route.push(vertex);

    for (Vertex neighbor = 0; neighbor < graph.vertices(); ++neighbor) {
      if (graph[vertex][neighbor] == 0.0f || visited[neighbor]) {
        continue;
      }

      stack.push(neighbor);

      visited[neighbor] = true;
    }
  }

  return route;
}

Route DijkstraShortestPath::operator()(const Graph &graph, const Vertex origin,
                                       const Vertex destination) const {
  vector<bool> visited(graph.vertices(), false);

  vector<Weight> weight(graph.vertices(), max_weight());

  vector<int> predecessors(graph.vertices(), -1);

  weight[origin] = 0.0f;

  for (uint32_t iteration = 0; iteration < graph.vertices() - 1; ++iteration) {
    uint32_t nearest = 0;

    auto minimum_weight = max_weight();

    for (uint32_t vertex = 0; vertex < graph.vertices(); ++vertex) {
      if (visited[vertex] || weight[vertex] > minimum_weight) {
        continue;
      }

      nearest = vertex;

      minimum_weight = weight[vertex];
    }

    visited[nearest] = true;

    for (uint32_t neighbor = 0; neighbor < graph.vertices(); ++neighbor) {
      const auto is_adjacent =
          graph[nearest][neighbor] != 0.0f && weight[nearest] != max_weight();

      const auto minimum_weight =
          weight[neighbor] <= weight[nearest] + graph[nearest][neighbor];

      if (!is_adjacent || visited[neighbor] || minimum_weight) {
        continue;
      }

      weight[neighbor] = weight[nearest] + graph[nearest][neighbor];

      predecessors[neighbor] = static_cast<int>(nearest);
    }
  }

  Route route;

  auto current_vertex = static_cast<int>(destination);

  while (current_vertex != -1 &&
         static_cast<uint32_t>(current_vertex) != origin) {
    route.push(static_cast<uint32_t>(current_vertex));

    current_vertex = predecessors[static_cast<uint32_t>(current_vertex)];
  }

  if (static_cast<uint32_t>(current_vertex) != origin) {
    route.clear();

    return route;
  }

  route.push(origin);

  route.reverse();

  return route;
}