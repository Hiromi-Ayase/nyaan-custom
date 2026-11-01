// Verify: matrix/linear-equation-hashmap.hpp
// GF(3)の全ベクトルを代入して解の有無を調べ、疎行列が返す特殊解を実際の式へ代入する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "hashmap/hashmap.hpp"

using mint = ModInt<3>;
#include "matrix/linear-equation-hashmap.hpp"

int main() {
  mt19937 rng(605);
  for (int n = 1; n <= 5; ++n) {
    for (int trial = 0; trial < 100; ++trial) {
      vector<HashMap<int, mint>> a(n);
      vector<mint> b(n);
      for (int i = 0; i < n; ++i) {
        b[i] = rng() % 3;
        for (int j = 0; j < n; ++j) {
          if (rng() % 3 == 0) {
            a[i][j] = rng() % 3;
          }
        }
      }
      int combinations = 1;
      for (int i = 0; i < n; ++i) {
        combinations *= 3;
      }
      auto satisfies = [&](const vector<mint>& x) {
        for (int i = 0; i < n; ++i) {
          mint sum = 0;
          for (auto [j, value] : a[i]) {
            sum += value * x[j];
          }
          if (sum != b[i]) {
            return false;
          }
        }
        return true;
      };
      bool exists = false;
      for (int mask = 0; mask < combinations; ++mask) {
        vector<mint> x(n);
        int digits = mask;
        for (auto& value : x) {
          value = digits % 3;
          digits /= 3;
        }
        exists = exists || satisfies(x);
      }
      auto got = LinearEquation_hashmap(a, b);
      // 未登録の0要素、特異な系、矛盾した系を含め、全解探索と存在判定が一致する。
      assert(!got.empty() == exists);
      if (exists) {
        // 特殊解の各成分を元の式へ代入すると、全行で右辺と一致する。
        assert(satisfies(got));
      }
    }
  }
}
