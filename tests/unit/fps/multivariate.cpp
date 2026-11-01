// Verify: fps/multivariate-fps.hpp
// 各変数の指数を復元して桁上がりを捨てる筆算で、多変数級数の積・逆数・指数を検査する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/multivariate-fps.hpp"

fps multiply(const fps& a, const fps& b, const vector<int>& base) {
  fps result(a.size());
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size(); ++j) {
      int x = i;
      int y = j;
      bool valid = true;
      for (int radix : base) {
        valid = valid && x % radix + y % radix < radix;
        x /= radix;
        y /= radix;
      }
      if (valid && i + j < (int)result.size()) {
        result[i + j] += a[i] * b[j];
      }
    }
  }
  return result;
}

int main() {
  using series = MultivariateFormalPowerSeries<mint>;
  mt19937 rng(2115);
  for (vector<int> base :
       vector<vector<int>>{{}, {1}, {2}, {3, 4}, {2, 3, 4}, {3, 3, 3, 3}, {2, 2, 2, 2, 2, 2, 2}}) {
    series a(base);
    series b(base);
    int n = a.f.size();
    for (auto& c : a.f) {
      c = rng();
    }
    for (auto& c : b.f) {
      c = rng();
    }
    // 積は各変数の打ち切り次数を超える項を捨てた筆算と一致する。
    assert((a * b).f == multiply(a.f, b.f, base));
    a.f[0] = 3;
    fps one(n);
    one[0] = 1;
    assert(multiply(a.f, a.inv().f, base) == one);
    assert(multiply((b / a).f, a.f, base) == b.f);
    a.f[0] = 0;
    fps expected(n);
    fps power = one;
    mint inverse_factorial = 1;
    int max_degree = 0;
    for (int radix : base) {
      max_degree += radix - 1;
    }
    for (int k = 0; k <= max_degree; ++k) {
      for (int i = 0; i < n; ++i) {
        expected[i] += power[i] * inverse_factorial;
      }
      power = multiply(power, a.f, base);
      inverse_factorial /= k + 1;
    }
    // exp(a)を有限個のa^k/k!の和で求める。定数項0なら必ず冪零になる。
    assert(a.exp().f == expected);
    series input(expected, base);
    assert(input.log().f == a.f);
    for (mint constant : {mint(0), mint(7)}) {
      a.f[0] = constant;
      power = one;
      for (int k = 0; k <= 7; ++k) {
        assert(a.pow(k).f == power);
        power = multiply(power, a.f, base);
      }
    }
  }
  series indexed(vector<int>{3, 4, 5});
  indexed(2, 3, 4) = 17;
  // 第一変数が最下位桁になる添字の規約を確認する。
  assert(indexed.id(2, 3, 4) == 59 && indexed.f[59] == 17);
}
