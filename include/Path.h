#pragma once

#include <list>

#include "Vertex.h"

using std::list;

class Path {
 public:
  Path(void) = default;

  void push(const Vertex);

  Vertex pop(void);

  list<Vertex>::iterator begin(void);

  list<Vertex>::iterator end(void);

  void clear(void);

  void sort(void);

 private:
  list<Vertex> vertices;
};
