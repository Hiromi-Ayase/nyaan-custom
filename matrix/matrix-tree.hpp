#pragma once

#include "matrix.hpp"

template <typename T>
struct MatrixTree {
  int n;
  Matrix<T> m;

  MatrixTree(int _n) : n(_n), m(_n) {
    assert(n > 0);
  }

  void add(int i, int j, const T& x) {
    if (i < n) {
      m[i][i] += x;
    }
    if (j < n) {
      m[j][j] += x;
    }
    if (i < n and j < n) {
      m[i][j] -= x;
      m[j][i] -= x;
    }
  }

  Matrix<T> get() const {
    return m;
  }

  T calc() const {
    return m.determinant();
  }
};

/**
 * @brief 行列木定理(ラプラシアン行列)
 * @docs docs/matrix/matrix-tree.md
 */
