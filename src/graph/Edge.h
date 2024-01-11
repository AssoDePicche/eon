#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"
#include "Weight.h"

class Edge {
 public:
  const Vertex origin;
  const Vertex destination;
  const Weight weight;

  Edge(const Vertex, const Vertex, const Weight);

  Vertex get_origin(void) const;

  Vertex get_destination(void) const;

  Weight get_weight(void) const;
};

bool operator<(const Edge&, const Edge&);

bool operator>(const Edge&, const Edge&);

bool operator==(const Edge&, const Edge&);

#endif
