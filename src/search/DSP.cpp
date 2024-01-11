#include "DSP.h"

#include <Weight.h>

#include <algorithm>
#include <cstdint>
#include <vector>

using std::reverse;
using std::uint32_t;
using std::vector;

Path DijkstraShortestPath::operator()(const Graph graph, const Vertex origin,
                                      const Vertex destination) {
  if (origin == destination) {
    return {};
  }

  vector<bool> visited(graph.get_number_of_vertices(), false);

  vector<Weight> weights(graph.get_number_of_vertices(), max_weight());

  vector<int> predecessors(graph.get_number_of_vertices(), -1);

  weights[origin] = 0;

  for (uint32_t iteration = 0; iteration < graph.get_number_of_vertices() - 1;
       ++iteration) {
    uint32_t nearest_vertex = 0;

    auto minimum_weight = max_weight();

    for (uint32_t vertex = 0; vertex < graph.get_number_of_vertices();
         ++vertex) {
      const auto visited_vertex = visited[vertex];

      const auto weight = weights[vertex];

      if (!visited_vertex && weight <= minimum_weight) {
        nearest_vertex = vertex;

        minimum_weight = weight;
      }
    }

    visited[nearest_vertex] = true;

    for (uint32_t adjacent_vertex = 0;
         adjacent_vertex < graph.get_number_of_vertices(); ++adjacent_vertex) {
      const auto edge_weight = graph[nearest_vertex][adjacent_vertex];

      const auto weight = weights[nearest_vertex];

      const auto new_weight = weight + edge_weight;

      const auto visited_vertex = visited[adjacent_vertex];

      const auto minimum_weight = weights[adjacent_vertex];

      if (edge_weight != 0 && !visited_vertex && weight != max_weight() &&
          new_weight < minimum_weight) {
        weights[adjacent_vertex] = new_weight;

        predecessors[adjacent_vertex] = static_cast<int>(nearest_vertex);
      }
    }
  }

  Path path;

  auto current_vertex = static_cast<int>(destination);

  while (current_vertex != -1 &&
         static_cast<uint32_t>(current_vertex) != origin) {
    path.push(static_cast<uint32_t>(current_vertex));

    current_vertex = predecessors[static_cast<uint32_t>(current_vertex)];
  }

  if (static_cast<uint32_t>(current_vertex) != origin) {
    path.clear();

    return path;
  }

  path.push(origin);

  reverse(path.begin(), path.end());

  return path;
}
