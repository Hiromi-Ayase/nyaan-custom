// Verify: math-fast/subset-convolution.hpp
// 非交差なマスク対を全列挙した集合畳み込みとSIMD版を比較する。
// 台集合0..9要素、全0、法-1、ランダムな係数とSIMDレーン未満の入力を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "math-fast/subset-convolution.hpp"

int main() {
  using M = LazyMontgomeryModInt<998244353>;
  mmint::set_mod<M>();
  mt19937 rng(382);
  for (int bits = 0; bits <= 9; ++bits) {
    for (int trial = 0; trial < 6; ++trial) {
      int n = 1 << bits;
      vector<M> a(n);
      vector<M> b(n);
      vector<M> expected(n);
      for (auto& x : a) {
        x = trial == 0 ? 0 : trial == 1 ? -1 : int(rng() % 101);
      }

      for (auto& x : b) {
        x = int(rng() % 101);
      }

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (!(i & j)) {
            expected[i | j] += a[i] * b[j];
          }
        }
      }

      // 各マスクの全部分集合を列挙して積を足した結果と、高速な畳み込みの全係数を比較する。
      assert(fast_multiply(a, b) == expected);
    }
  }
}
