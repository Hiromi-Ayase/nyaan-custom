#pragma once

#include "matrix-tree.hpp"
#include "polynomial-matrix-determinant.hpp"

// 多項式の辺重みを持つ行列木定理。係数の型mintとFPSの乗算実装を用意する。
template <typename mint>
struct PolynomialMatrixTree : MatrixTree<FormalPowerSeries<mint>> {
  using Base = MatrixTree<FormalPowerSeries<mint>>;
  using Base::Base;

  FormalPowerSeries<mint> calc() const {
    return PolynomialMatrixDeterminant(this->m);
  }
};

/**
 * @brief 多項式の辺重みに対応した行列木定理
 * @docs docs/matrix/polynomial-matrix-tree.md
 */
