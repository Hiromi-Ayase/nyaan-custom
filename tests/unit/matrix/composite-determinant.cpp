// Verify: matrix/determinant-arbitrary-mod.hpp
// 逆元を使えない合成数の法でも、置換の符号付き積の和から行列式を直接照合する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/arbitrary-modint.hpp"
#include "matrix/determinant-arbitrary-mod.hpp"

int main() {
  using M = ArbitraryModIntBase<604>;
  mt19937 rng(604);
  for (int mod : {1, 2, 4, 6, 12, 101, 1000, 1000000000}) {
    M::set_mod(mod);
    for (int n = 0; n <= 5; ++n) {
      for (int trial = 0; trial < 60; ++trial) {
        vector<vector<M>> a(n, vector<M>(n));
        for (auto& row : a) {
          for (auto& x : row) {
            x = trial == 0 ? 0 : rng() % mod;
          }
        }
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        long long expected = 0;
        do {
          long long term = 1 % mod;
          for (int i = 0; i < n; ++i) {
            term = term * a[i][p[i]].get() % mod;
            for (int j = 0; j < i; ++j) {
              if (p[j] > p[i]) {
                term = (mod - term) % mod;
              }
            }
          }
          expected = (expected + term) % mod;
        } while (next_permutation(p.begin(), p.end()));
        // 除算を一切使わない定義式との比較により、非可逆なピボットも検証できる。
        assert(determinant_arbitrary_mod(a).get() == expected);
      }
    }
  }
}
