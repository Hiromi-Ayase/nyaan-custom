// Verify: fps/online-fps.hpp
// 遅延計算する係数を筆算と比較し、自己参照のCatalan級数も低次からのDPで検証する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/online-fps.hpp"

fps multiply(const fps& a, const fps& b, int n) {
  fps result(n);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size() && i + j < n; ++j) {
      result[i + j] += a[i] * b[j];
    }
  }
  return result;
}

int main() {
  mt19937 rng(2113);
  const int n = 257;
  fps a(n);
  fps b(n);
  for (auto& c : a) {
    c = rng();
  }
  for (auto& c : b) {
    c = rng();
  }
  a[0] = 1;
  b[0] = 3;
  ofps left(a);
  ofps right(b);
  auto product = left * right;
  auto quotient = left / right;
  auto inverse = right.inv();
  auto sum = left + right;
  auto difference = left - right;
  auto derivative = left.diff();
  auto integral = left.integral();
  auto shifted = left << 3;
  auto logarithm = left.log();
  fps exp_input = a;
  exp_input[0] = 0;
  ofps input(exp_input);
  auto exponential = input.exp();
  fps expected_exp(n);
  expected_exp[0] = 1;
  for (int k = 1; k < n; ++k) {
    for (int j = 1; j <= k; ++j) {
      expected_exp[k] += exp_input[j] * j * expected_exp[k - j];
    }
    expected_exp[k] /= k;
  }
  fps expected_product = multiply(a, b, n);
  // 未来の係数を先に要求した後、過去の係数も変化せず再利用できる。
  assert(product[n - 1] == expected_product[n - 1]);
  for (int i = n - 1; i >= 0; --i) {
    assert(product[i] == expected_product[i]);
    assert(sum[i] == a[i] + b[i] && difference[i] == a[i] - b[i]);
    assert(exponential[i] == expected_exp[i]);
    assert(integral[i] == (i == 0 ? mint(0) : a[i - 1] / i));
    assert(derivative[i] == (i + 1 < n ? a[i + 1] * (i + 1) : mint(0)));
    assert(shifted[i] == (i < 3 ? mint(0) : a[i - 3]));
  }
  fps one(n);
  one[0] = 1;
  assert(multiply(inverse.pre(n), b, n) == one);
  assert(multiply(quotient.pre(n), b, n) == a);
  fps log = logarithm.pre(n);
  fps exp_log(n);
  exp_log[0] = 1;
  for (int k = 1; k < n; ++k) {
    for (int j = 1; j <= k; ++j) {
      exp_log[k] += log[j] * j * exp_log[k - j];
    }
    exp_log[k] /= k;
  }
  assert(exp_log == a);
  ofps catalan;
  catalan.set_corner(fps{1});
  auto square = catalan * catalan;
  auto recurrence = square << 1;
  catalan.set(recurrence);
  fps expected(n);
  expected[0] = 1;
  for (int k = 1; k < n; ++k) {
    for (int i = 0; i < k; ++i) {
      expected[k] += expected[i] * expected[k - 1 - i];
    }
  }
  // C=1+x*C^2の自己参照が、係数を必要な順に計算できる。
  assert(catalan.pre(n) == expected);
}
