#include <RouteAssignmentStrategy.h>

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