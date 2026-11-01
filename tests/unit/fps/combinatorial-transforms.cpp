// Verify: fps/stirling-matrix.hpp
// Verify: fps/pascal-matrix.hpp
// Verify: fps/composite-exp.hpp
// Pascal/Stirlingの三角形を漸化式で作り、行列作用と転置・逆変換を検査する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/stirling-matrix.hpp"
#include "fps/pascal-matrix.hpp"
#include "fps/composite-exp.hpp"

int main() {
  mt19937 rng(2105);
  for (int n : {0, 1, 2, 3, 17, 64, 65, 129}) {
    vector<fps> pascal(n, fps(n));
    vector<fps> stirling(n, fps(n));
    vector<fps> first(n, fps(n));
    if (n > 0) {
      pascal[0][0] = 1;
      stirling[0][0] = 1;
      first[0][0] = 1;
    }
    for (int i = 1; i < n; ++i) {
      pascal[i][0] = 1;
      for (int j = 1; j <= i; ++j) {
        pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        stirling[i][j] = stirling[i - 1][j - 1] + stirling[i - 1][j] * j;
        first[i][j] = first[i - 1][j - 1] - first[i - 1][j] * (i - 1);
      }
    }
    fps a(n);
    for (auto& c : a) {
      c = rng();
    }
    for (bool inverse : {false, true}) {
      for (bool transpose : {false, true}) {
        fps p(n);
        fps s(n);
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            int row = transpose ? j : i;
            int col = transpose ? i : j;
            mint sign = inverse && ((row - col) & 1) ? -1 : 1;
            p[i] += pascal[row][col] * sign * a[j];
            s[i] += (inverse ? first[row][col] : stirling[row][col]) * a[j];
          }
        }
        // 逆行列は符号付き二項係数/第一種Stirling数を使って直接掛ける。
        assert((transpose ? pascal_matrix_trans(a, inverse) : pascal_matrix(a, inverse)) == p);
        assert((transpose ? stirling_matrix_trans(a, inverse) : stirling_matrix(a, inverse)) == s);
      }
    }
    if (n == 0) {
      continue;
    }
    for (mint c : {mint(1), mint(7), mint(-3)}) {
      fps expected(n);
      for (int i = 0; i < n; ++i) {
        mint coefficient = 1;
        for (int k = 0; k < n; ++k) {
          expected[k] += a[i] * coefficient;
          coefficient *= c * i;
          coefficient /= k + 1;
        }
      }
      // exp(c*i*x)を項ごとに展開した係数と、逆変換による復元を検証する。
      assert(composite_exp(a, c) == expected);
      assert(inverse_of_composite_exp(expected, c) == a);
    }
  }
}
