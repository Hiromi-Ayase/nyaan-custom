// Verify: fps/fps-composition-old.hpp
// 関数合成を冪の筆算で比較し、定数項・先頭の零・2の冪境界を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "modulo/binomial.hpp"
#include "fps/fps-composition-old.hpp"

fps multiply(const fps& a, const fps& b, int n) {
  fps result(n);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size() && i + j < n; ++j) {
      result[i + j] += a[i] * b[j];
    }
  }
  return result;
}

// gの各項ごとにfの冪を作り、合成の定義どおりに加算する。
fps substitute(const fps& f, const fps& g, int n) {
  fps result(n);
  fps power(n);
  if (n > 0) {
    power[0] = 1;
  }
  for (auto c : g) {
    for (int i = 0; i < n; ++i) {
      result[i] += power[i] * c;
    }
    power = multiply(power, f, n);
  }
  return result;
}

int main() {
  mt19937 rng(2106);
  Binomial<mint> binomial;
  for (int n : {1, 2, 3, 7, 16, 31, 32, 33, 65, 129}) {
    for (int pattern = 0; pattern < 5; ++pattern) {
      fps a(n);
      fps b(n);
      for (auto& c : b) {
        c = rng();
      }
      for (int i = 0; i < n; ++i) {
        if (pattern == 0 || (pattern < 4 && i >= pattern)) {
          a[i] = rng();
        }
      }
      // 外側bと内側aを取り違えず、b(a(x))の係数すべてを比較する。
      assert(Composition(a, b, binomial, n) == substitute(a, b, n));
    }
  }
}
