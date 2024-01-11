#include "BFS.h"

#include <queue>
#include <vector>

using std::queue;
using std::vector;

Path BreadthFirstSearch::operator()(const Graph graph, const Vertex origin) {
  vector<bool> visited(graph.get_number_of_vertices(), false);

  queue<Vertex> queue;

  queue.push(origin);

  visited[origin] = true;

  Path path;

  while (!queue.empty()) {
    auto vertex = queue.front();

    queue.pop();

    path.push(vertex);

    for (const auto &neighbor : graph.neighbors_of(vertex)) {
      if (!visited[neighbor]) {
        queue.push(neighbor);

        visited[neighbor] = true;
      }
    }
  }

  return path;
}
