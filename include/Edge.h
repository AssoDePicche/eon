#pragma once

#include "Vertex.h"
#include "Weight.h"

class Edge {
 public:
  const Vertex origin, destination;
  const Weight weight;

  Edge(const Vertex, const Vertex, const Weight);

  Vertex get_origin(void) const;

  Vertex get_destination(void) const;

  Weight get_weight(void) const;
};

bool operator<(const Edge&, const Edge&);

bool operator>(const Edge&, const Edge&);

bool operator==(const Edge&, const Edge&);
