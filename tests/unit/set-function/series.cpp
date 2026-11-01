// Verify: set-function/exp-of-set-power-series.hpp
// Verify: set-function/polynomial-composite-set-power-series.hpp
// 集合畳み込みを全マスク対の二重ループで実装し、冪の繰り返し乗算からexpと多項式合成を計算する。
// 台集合0..6要素、非零定数項を持つ合成、係数が全て0の場合を含める。
#include <bits/stdc++.h>
using namespace std;
#include "fps/ntt-friendly-fps.hpp"
#include "modint/montgomery-modint.hpp"
#include "set-function/exp-of-set-power-series.hpp"
#include "set-function/polynomial-composite-set-power-series.hpp"

int main() {
  using M = LazyMontgomeryModInt<998244353>;
  using FPS = FormalPowerSeries<M>;
  mt19937 rng(8773);
  for (int bits = 0; bits <= 6; ++bits) {
    for (int trial = 0; trial < 12; ++trial) {
      int n = 1 << bits;
      vector<M> g(n);
      for (auto& x : g) {
        x = trial ? rng() % 101 : 0;
      }

      auto mul = [&](const vector<M>& a, const vector<M>& b) {
        vector<M> c(n);
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            if (!(i & j)) {
              c[i | j] += a[i] * b[j];
            }
          }
        }

        return c;
      };
      FPS f(bits + 4);
      for (auto& x : f) {
        x = rng() % 101;
      }

      vector<M> expected(n);
      vector<M> power(n);
      power[0] = 1;
      for (auto c : f) {
        for (int i = 0; i < n; ++i) {
          expected[i] += c * power[i];
        }

        power = mul(power, g);
      }

      // 素朴な部分集合畳み込みで各冪を作り、係数を掛けて足した合成結果と比較する。
      assert((polynomial_composite_set_power_series<M, 6>(bits, f, g) == expected));
      g[0] = 0;
      expected.assign(n, 0);
      power.assign(n, 0);
      power[0] = 1;
      M factorial = 1;
      for (int k = 0; k <= bits; ++k) {
        if (k) {
          factorial *= k;
        }

        for (int i = 0; i < n; ++i) {
          expected[i] += power[i] / factorial;
        }

        power = mul(power, g);
      }

      // expの定義どおりにg^k/k!を素朴に足した結果と比較する。定数項は0に設定する。
      assert((exp_of_set_power_series<M, 6>(bits, g) == expected));
    }
  }
}
