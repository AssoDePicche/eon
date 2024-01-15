#include "Matrix.h"

Matrix::Matrix(const uint32_t m, const uint32_t n) : rows(m), columns(n) {
  data = vector(rows, vector<Weight>(columns, 0.0f));
}

Matrix::Matrix(const uint32_t n) : rows(n), columns(n) {
  data = vector(rows, vector<Weight>(columns, 0.0f));
}

uint32_t Matrix::get_rows(void) const { return rows; }

uint32_t Matrix::get_columns(void) const { return columns; }

vector<Weight>& Matrix::operator[](const uint32_t row) { return data[row]; }

const vector<Weight>& Matrix::operator[](const uint32_t row) const {
  return data[row];
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  for (uint32_t i = 0; i < matrix.get_rows(); ++i) {
    for (uint32_t j = 0; j < matrix.get_columns(); ++j) {
      out << matrix[i][j] << ' ';
    }

    out << '\n';
  }

  return out;
}

Matrix Matrix::make_identity_matrix(const uint32_t n) {
  Matrix matrix(n);

  for (uint32_t i = 0; i < n; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (i == j) {
        matrix[i][j] = 1.0f;
      }
    }
  }

  return matrix;
}
