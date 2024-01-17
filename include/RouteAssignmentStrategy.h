#pragma once

#include <list>

#include "Graph.h"

using std::list;

class Route {
 public:
  Route(void) = default;

  Route(list<Vertex> vertices);

  list<Vertex>::iterator begin(void);

  void clear(void);

  Vertex dequeue(void);

  bool empty(void) const;

  list<Vertex>::iterator end(void);

  void enqueue(const Vertex);

  Vertex pop(void);

  void push(const Vertex);

  void reverse(void);

  void sort(void);

 private:
  list<Vertex> vertices;
};

class RouteAssignmentStrategy {
 public:
  virtual Route operator()(const Graph &, const Vertex, const Vertex) const = 0;
};