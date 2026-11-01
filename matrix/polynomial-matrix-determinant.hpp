#pragma once



#include "../fps/formal-power-series.hpp"
#include "../fps/polynomial-interpolation.hpp"
#include "matrix.hpp"

template <typename mint>
FormalPowerSeries<mint> PolynomialMatrixDeterminant(
    const Matrix<FormalPowerSeries<mint>> &m) {
  int N = m.size();
  int deg = 0;
  // 各置換の積は各行から1項ずつ選ぶため、各行の最大次数の和を上界にする。
  // 対角成分だけでは、非対角成分の次数が高い行列の補間点が不足する。
  for (int i = 0; i < N; ++i) {
    int row_degree = 0;
    for (int j = 0; j < N; ++j) {
      row_degree = max(row_degree, int(m[i][j].size()) - 1);
    }
    deg += row_degree;
  }
  vector<mint> xs(deg + 1);
  vector<mint> ys(deg + 1);
  Matrix<mint> M(N);
  for (int x = 0; x <= deg; x++) {
    xs[x] = x;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j) M[i][j] = m[i][j].eval(x);
    ys[x] = M.determinant();
  }
  return PolynomialInterpolation<mint>(xs, ys);
}

/**
 * @brief 多項式行列の行列式
 * @docs docs/matrix/polynomial-matrix-determinant.md
 */
