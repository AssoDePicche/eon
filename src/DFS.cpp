#include "DFS.h"

#include <stack>
#include <vector>

using std::stack;
using std::vector;

Path DepthFirstSearch::operator()(const Graph& graph, const Vertex origin) {
  vector<bool> visited(graph.get_number_of_vertices(), false);

  stack<Vertex> stack;

  stack.push(origin);

  visited[origin] = true;

  Path path;

  while (!stack.empty()) {
    const auto vertex = stack.top();

    stack.pop();

    path.push(vertex);

    for (const auto& neighbors : graph.neighbors_of(vertex)) {
      if (!visited[neighbors]) {
        stack.push(neighbors);

        visited[neighbors] = true;
      }
    }
  }

  path.sort();

  return path;
}
