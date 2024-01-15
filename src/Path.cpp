#include "Path.h"

void Path::push(const Vertex vertex) { vertices.push_back(vertex); }

Vertex Path::pop(void) {
  const auto vertex = vertices.back();

  vertices.pop_back();

  return vertex;
}

list<Vertex>::iterator Path::begin(void) { return vertices.begin(); }

list<Vertex>::iterator Path::end(void) { return vertices.end(); }

void Path::clear(void) { vertices.clear(); }

void Path::sort(void) { vertices.sort(); }
