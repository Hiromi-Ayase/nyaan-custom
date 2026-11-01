// Verify: matrix/black-box-linear-algebra.hpp
// 乱数種を固定し、密・疎の行列ベクトル積と冪を直接計算、行列式を置換列挙で照合する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
#include "matrix/black-box-linear-algebra.hpp"

using M = LazyMontgomeryModInt<998244353>;
using F = FormalPowerSeries<M>;

int main() {
  mt19937 random(610);
  for (int n = 1; n <= 5; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      ModMatrix<M> dense(n);
      SparseMatrix<M> sparse(n);
      vector<vector<M>> a(n, vector<M>(n));
      for (int step = 0; step < n * n; ++step) {
        int i = random() % n;
        int j = random() % n;
        M x = trial == 0 ? 0 : random() % 11;
        dense.add(i, j, x);
        sparse.add(i, j, x);
        a[i][j] += x;
      }
      int row = random() % n;
      M factor = random() % 5;
      dense.apply(row, factor);
      sparse.apply(row, factor);
      for (auto& x : a[row]) {
        x *= factor;
      }
      F b(n);
      for (auto& x : b) {
        x = random() % 101;
      }
      F expected = b;
      for (int k = 0; k <= 10; ++k) {
        // 密行列版の冪作用を、ベクトルに1回ずつ行列を掛けた値と比較する。
        assert(fast_pow<M>(dense, b, k) == expected);
        // 疎行列版でも、重複座標の加算や行の倍率変更後に同じ結果になる。
        assert(fast_pow<M>(sparse, b, k) == expected);
        F next(n);
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            next[i] += a[i][j] * expected[j];
          }
        }
        expected = next;
      }
      vector<int> p(n);
      iota(p.begin(), p.end(), 0);
      M det = 0;
      do {
        M term = 1;
        for (int i = 0; i < n; ++i) {
          term *= a[i][p[i]];
          for (int j = 0; j < i; ++j) {
            if (p[j] > p[i]) {
              term = -term;
            }
          }
        }
        det += term;
      } while (next_permutation(p.begin(), p.end()));
      // 乱択した最小多項式から求める行列式を、定義式で全列挙した値と比較する。
      assert(fast_det<M>(dense) == det);
      // 疎行列でも、特異な行列を含め同じ行列式を返す。
      assert(fast_det<M>(sparse) == det);
    }
  }
}
