// Verify: modulo/gauss-elimination-fast.hpp
// SIMD消去法の行列式を置換全列挙と比較し、連立方程式の特殊解・核基底を元の式へ代入する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modint/montgomery-modint.hpp"
#include "modulo/gauss-elimination-fast.hpp"

using M = LazyMontgomeryModInt<998244353>;

int main() {
  mt19937 rng(613);
  for (int n = 1; n <= 6; ++n) {
    for (int trial = 0; trial < 60; ++trial) {
      vector<vector<M>> a(n, vector<M>(n));
      for (auto& row : a) {
        for (auto& x : row) {
          x = trial == 0 ? 0 : rng() % 7;
        }
      }
      vector<int> p(n);
      iota(p.begin(), p.end(), 0);
      M expected = 0;
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
        expected += term;
      } while (next_permutation(p.begin(), p.end()));
      // 行交換の符号や0行を含め、除算を使わない行列式の定義と一致する。
      assert(Gauss::determinant(a) == expected);
    }
  }

  for (int n : {1, 7, 8, 9, 15, 16, 17, 33}) {
    vector<vector<M>> a(n, vector<M>(n + 2));
    vector<M> known(n + 2);
    vector<M> b(n);
    for (auto& x : known) {
      x = rng() % M::get_mod();
    }
    for (int i = 0; i < n; ++i) {
      a[i][i] = 1;
      for (int j = n; j < n + 2; ++j) {
        a[i][j] = rng() % M::get_mod();
      }
      for (int j = 0; j < n + 2; ++j) {
        b[i] += a[i][j] * known[j];
      }
    }
    auto basis = Gauss::LinearEquation(a, b);
    // 左側に単位行列を持つので階数はn、自由変数は2個。特殊解と2本の基底を返す。
    assert(basis.size() == 3);
    for (int t = 0; t < (int)basis.size(); ++t) {
      for (int i = 0; i < n; ++i) {
        M value = 0;
        for (int j = 0; j < n + 2; ++j) {
          value += a[i][j] * basis[t][j];
        }
        // 特殊解は右辺を満たし、各方向ベクトルは同次方程式を満たす。
        assert(value == (t == 0 ? b[i] : M(0)));
      }
    }
    a.push_back(vector<M>(n + 2));
    b.push_back(1);
    // 0=1という行を追加した系には解がない。
    assert(Gauss::LinearEquation(a, b).empty());
  }
}
