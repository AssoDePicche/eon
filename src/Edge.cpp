#include "Edge.h"

Edge::Edge(const Vertex u, const Vertex v, const Weight w)
    : origin(u), destination(v), weight(w) {}

Vertex Edge::get_origin(void) const { return origin; }

Vertex Edge::get_destination(void) const { return destination; }

Weight Edge::get_weight(void) const { return weight; }

bool operator<(const Edge &uv, const Edge &uw) {
  return uv.get_weight() < uw.get_weight();
}

bool operator>(const Edge &uv, const Edge &uw) { return !(uv < uw); }

bool operator==(const Edge &uv, const Edge &wx) {
  const auto same_origin = uv.get_origin() == wx.get_origin();

  const auto same_destination = uv.get_destination() == wx.get_destination();

  return same_origin && same_destination;
}
