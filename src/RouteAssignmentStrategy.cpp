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
      if (graph[vertex][neighbor] != 0.0f && !visited[neighbor]) {
        queue.push(neighbor);

        visited[neighbor] = true;
      }
    }
  }

  return route;
}