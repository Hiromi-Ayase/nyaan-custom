// Verify: math/rational-fps.hpp
// 係数ごとの素朴な畳み込み・逆数の漸化式・exp/logの定義による有限和で、有理数FPSを照合する。
#include <bits/stdc++.h>
using namespace std;
#include "math/rational-fps.hpp"

using R = RationalBase<__int128, __int128>;
using F = FormalPowerSeries_rational<R>;

F multiply(const F& a, const F& b, int degree) {
  F result(degree);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size() && i + j < degree; ++j) {
      result[i + j] += a[i] * b[j];
    }
  }
  return result;
}

int main() {
  mt19937 rng(712);
  for (int n = 1; n <= 6; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      F f(n);
      for (auto& x : f) {
        x = int(rng() % 5) - 2;
      }
      f[0] = 1;
      F inverse(n);
      inverse[0] = 1;
      for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= i; ++j) {
          inverse[i] -= f[j] * inverse[i - j];
        }
      }
      // f*g=1の各係数を順に解いた逆数と比較し、Newton法に依存しない期待値を使う。
      assert(f.inv(n) == inverse);
      F g = f;
      g[0] = 0;
      F power(n);
      power[0] = 1;
      F exponential(n);
      F logarithm(n);
      long long factorial = 1;
      for (int k = 0; k < n; ++k) {
        if (k) {
          factorial *= k;
        }
        for (int i = 0; i < n; ++i) {
          exponential[i] += power[i] / R(factorial);
          if (k) {
            logarithm[i] += power[i] * R(k % 2 ? 1 : -1, k);
          }
        }
        power = multiply(power, g, n);
      }
      // exp(g)=Σg^k/k!を直接足した値と、全係数が一致する。
      assert(g.exp(n) == exponential);
      // log(1+g)=Σ(-1)^(k+1)g^k/kを直接足した値と一致する。
      assert(f.log(n) == logarithm);
      power.assign(n, R(0));
      power[0] = 1;
      for (int k = 0; k <= 4; ++k) {
        // 冪を1回ずつ素朴に掛けた値と比較し、0乗も確認する。
        assert(f.pow(k, n) == power);
        power = multiply(power, f, n);
      }
      // 積分した係数を微分すると、元の係数が過不足なく戻る。
      assert(f.integral().diff() == f);
      for (int x = -2; x <= 2; ++x) {
        R expected = 0;
        R xp = 1;
        for (R c : f) {
          expected += c * xp;
          xp *= x;
        }
        // 各項を直接代入して足した値と、評価APIの結果が一致する。
        assert(f.eval(R(x)) == expected);
      }
      F divisor{1, 1};
      F quotient{2, -1, 1};
      F dividend = multiply(divisor, quotient, 4);
      dividend[0] += 3;
      // 既知の商と定数の余りから被除数を構成し、多項式除算で復元できる。
      assert(dividend / divisor == quotient);
      assert(dividend % divisor == F{R(3)});
    }
  }
}
