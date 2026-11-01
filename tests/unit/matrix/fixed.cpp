// Verify: matrix/matrix-fast.hpp
// 固定サイズ行列の加減乗算・冪・行列式を、配列での直接計算と置換列挙で比較する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "matrix/matrix-fast.hpp"

using M = ModInt<101>;

template <int N>
void check() {
  mt19937 rng(603 + N);
  for (int trial = 0; trial < 80; ++trial) {
    Matrix<M, N, N> a;
    Matrix<M, N, N> b;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        a[i][j] = rng() % 101;
        b[i][j] = rng() % 101;
      }
    }
    auto product = a * b;
    auto sum = a + b;
    auto difference = a - b;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        M expected = 0;
        for (int k = 0; k < N; ++k) {
          expected += a[i][k] * b[k][j];
        }
        // 各成分の和・差・積を、それぞれ独立に計算した値と比較する。
        assert(sum[i][j] == a[i][j] + b[i][j]);
        assert(difference[i][j] == a[i][j] - b[i][j]);
        assert(product[i][j] == expected);
      }
    }
    vector<int> permutation(N);
    iota(permutation.begin(), permutation.end(), 0);
    M det = 0;
    do {
      M term = 1;
      for (int i = 0; i < N; ++i) {
        term *= a[i][permutation[i]];
        for (int j = 0; j < i; ++j) {
          if (permutation[j] > permutation[i]) {
            term = -term;
          }
        }
      }
      det += term;
    } while (next_permutation(permutation.begin(), permutation.end()));
    // 置換の符号付き積の和と比較し、行交換や特異行列の扱いを確認する。
    assert(a.determinant() == det);

    auto expected = Matrix<M, N, N>::I().A;
    for (int k = 0; k <= 10; ++k) {
      // 0乗を単位行列とし、1回ずつ掛けた結果を二乗法と比較する。
      assert((a ^ k).A == expected);
      decltype(expected) next{};
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          for (int t = 0; t < N; ++t) {
            next[i][j] += expected[i][t] * a[t][j];
          }
        }
      }
      expected = next;
    }
  }
}

int main() {
  check<1>();
  check<2>();
  check<3>();
  check<5>();
}
