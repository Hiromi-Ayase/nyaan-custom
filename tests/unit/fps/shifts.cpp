// Verify: fps/lagrange-interpolation-point.hpp
// Verify: fps/sample-point-shift.hpp
// Verify: fps/taylor-shift.hpp
// 連続点の補間を直接評価と比較し、係数の平行移動を二項展開で検査する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/lagrange-interpolation-point.hpp"
#include "fps/sample-point-shift.hpp"
#include "fps/taylor-shift.hpp"

mint evaluate(const fps& f, mint x) {
  mint result = 0;
  for (int i = int(f.size()) - 1; i >= 0; --i) {
    result = result * x + f[i];
  }
  return result;
}

int main() {
  Binomial<mint> binomial;
  mt19937 rng(2104);
  for (int n : {1, 2, 3, 16, 63, 64, 65, 129}) {
    fps f(n);
    fps samples(n);
    for (auto& c : f) {
      c = rng();
    }
    for (int i = 0; i < n; ++i) {
      samples[i] = evaluate(f, i);
    }
    for (long long t : {0LL, 1LL, (long long)n - 1, (long long)n, 1234567890123LL, 998244351LL}) {
      // 既知の点、範囲外の点、法をまたぐ大きな点でも同じ多項式を評価する。
      assert(lagrange_interpolation(vector<mint>(samples), t, binomial) == evaluate(f, t));
      for (int count : {0, 1, n + 3}) {
        fps expected(count);
        for (int i = 0; i < count; ++i) {
          expected[i] = evaluate(f, mint(t) + i);
        }
        assert(SamplePointShift(samples, mint(t), count) == expected);
      }
      fps expected(n);
      // (x+t)^i を1次式の繰り返し乗算で展開する。
      fps power{1};
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
          expected[j] += f[i] * power[j];
        }
        fps next(power.size() + 1);
        for (int j = 0; j < (int)power.size(); ++j) {
          next[j] += power[j] * t;
          next[j + 1] += power[j];
        }
        power = next;
      }
      assert(TaylorShift(f, mint(t), binomial) == expected);
    }
  }
  assert(TaylorShift(fps{}, mint(7), binomial).empty());
}
