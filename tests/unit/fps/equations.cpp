// Verify: fps/pow-enumerate.hpp
// Verify: fps/fps-compositional-inverse.hpp
// Verify: fps/newton-method.hpp
// Verify: fps/differential-equation.hpp
// 冪の係数列挙、逆関数、Newton法、常微分方程式を係数ごとの定義で検査する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/pow-enumerate.hpp"
#include "fps/fps-compositional-inverse.hpp"
#include "fps/newton-method.hpp"
#include "fps/differential-equation.hpp"

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
  mt19937 rng(2107);
  for (int n : {2, 3, 8, 16, 31, 32, 33, 65, 129}) {
    fps a(n);
    fps b(n);
    for (auto& c : a) {
      c = rng();
    }
    for (auto& c : b) {
      c = rng();
    }
    for (mint constant : {mint(0), mint(3)}) {
      a[0] = constant;
      fps expected(n + 4);
      fps power = b;
      for (int i = 0; i < (int)expected.size(); ++i) {
        expected[i] = power[n - 1];
        power = multiply(power, a, n);
      }
      // 各冪を順に掛けた最高次係数と、まとめて求めた列を比較する。
      assert(pow_enumerate(a, b, n + 3) == expected);
    }
    a[0] = 0;
    a[1] = 7;
    fps identity(n);
    identity[1] = 1;
    auto inverse = compositional_inverse(a);
    // 左右どちらから合成してもxになることを、独立した合成処理で確認する。
    assert(substitute(inverse, a, n) == identity);
    assert(substitute(a, inverse, n) == identity);
    function<fps(fps, int)> calc = [&](fps f, int degree) { return substitute(f, a, degree); };
    auto callback_inverse = compositional_inverse<fps>(calc, n);
    assert(callback_inverse == inverse);
    b[0] = 1;
    fps square = multiply(b, b, n);
    function<pair<fps, fps>(fps, int)> equation = [&](fps f, int degree) {
      return make_pair((f * f - square).pre(degree), (f * 2).pre(degree));
    };
    // G(f)=f^2-b^2の初期値1を選ぶと、求める枝はb自身になる。
    assert(newton_method<fps>(equation, mint(1), n) == b);
    function<fps(fps, int)> rhs = [](fps f, int degree) { return (f * f + mint(1)).pre(degree); };
    function<fps(fps, int)> derivative = [](fps f, int degree) { return (f * 2).pre(degree); };
    fps expected(n);
    expected[0] = 3;
    for (int k = 0; k + 1 < n; ++k) {
      mint value = k == 0 ? 1 : 0;
      for (int i = 0; i <= k; ++i) {
        value += expected[i] * expected[k - i];
      }
      expected[k + 1] = value / (k + 1);
    }
    // f'=1+f^2の各次数を低次から決める漸化式と比較する。
    assert(DifferentialEquation<mint>(rhs, derivative, 3, n) == expected);
  }
}
