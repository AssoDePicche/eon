#pragma once

#include <cstdint>
#include <ostream>
#include <vector>

#include "Weight.h"

using std::ostream;
using std::uint32_t;
using std::vector;

class Matrix {
 public:
  Matrix(void) = default;

  Matrix(const uint32_t, const uint32_t);

  Matrix(const uint32_t);

  uint32_t get_rows(void) const;

  uint32_t get_columns(void) const;

  vector<Weight>& operator[](const uint32_t);

  const vector<Weight>& operator[](const uint32_t) const;

  friend ostream& operator<<(ostream&, const Matrix&);

  static Matrix make_identity_matrix(const uint32_t);

 private:
  vector<vector<Weight>> data;
  uint32_t rows = 0;
  uint32_t columns = 0;
};
