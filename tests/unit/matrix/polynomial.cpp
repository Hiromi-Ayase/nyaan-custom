// Verify: matrix/polynomial-matrix-determinant.hpp
// Verify: matrix/polynomial-matrix-prefix-prod.hpp
// 多項式行列式を置換と係数の全列挙で求め、連続積を各整数への直接代入と三重ループで比較する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
#include "matrix/polynomial-matrix-determinant.hpp"
#include "matrix/polynomial-matrix-prefix-prod.hpp"

using M = LazyMontgomeryModInt<998244353>;
using F = FormalPowerSeries<M>;

vector<M> multiply(const vector<M>& a, const vector<M>& b) {
  if (a.empty() || b.empty()) {
    return {};
  }
  vector<M> c(a.size() + b.size() - 1);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size(); ++j) {
      c[i + j] += a[i] * b[j];
    }
  }
  return c;
}

int main() {
  mt19937 rng(609);
  for (int n = 1; n <= 4; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      Matrix<F> a(n);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          int length = trial == 0 ? (i == j ? 1 : 4) : rng() % 5;
          a[i][j].resize(length);
          for (auto& x : a[i][j]) {
            x = rng() % 11;
          }
        }
      }
      vector<int> p(n);
      iota(p.begin(), p.end(), 0);
      vector<M> expected(n * 4 + 1);
      do {
        vector<M> term{1};
        for (int i = 0; i < n; ++i) {
          term = multiply(term, a[i][p[i]]);
          for (int j = 0; j < i; ++j) {
            if (p[j] > p[i]) {
              for (auto& x : term) {
                x = -x;
              }
            }
          }
        }
        for (int i = 0; i < (int)term.size(); ++i) {
          expected[i] += term[i];
        }
      } while (next_permutation(p.begin(), p.end()));
      auto got = PolynomialMatrixDeterminant(a);
      while (!expected.empty() && expected.back() == 0) {
        expected.pop_back();
      }
      while (!got.empty() && got.back() == 0) {
        got.pop_back();
      }
      // 対角成分より非対角成分の次数が高い場合も、全列挙した行列式の全係数と一致する。
      assert(vector<M>(got.begin(), got.end()) == expected);

      if (n <= 3) {
        for (int k : {0, 1, 2, 3, 7, 16, 33, 100}) {
          vector<vector<M>> product(n, vector<M>(n));
          for (int i = 0; i < n; ++i) {
            product[i][i] = 1;
          }
          for (int x = 0; x < k; ++x) {
            vector<vector<M>> evaluated(n, vector<M>(n));
            for (int i = 0; i < n; ++i) {
              for (int j = 0; j < n; ++j) {
                M power = 1;
                for (M c : a[i][j]) {
                  evaluated[i][j] += c * power;
                  power *= x;
                }
              }
            }
            vector<vector<M>> next(n, vector<M>(n));
            for (int i = 0; i < n; ++i) {
              for (int j = 0; j < n; ++j) {
                for (int t = 0; t < n; ++t) {
                  next[i][j] += evaluated[i][t] * product[t][j];
                }
              }
            }
            product = next;
          }
          // 積の順番はA(k-1)...A(0)。非可換な行列で順序とk=0の単位行列を確認する。
          assert(polynomial_matrix_prod(a, k).A == product);
        }
      }
    }
  }
}
