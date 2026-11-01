// Verify: math/bigint-all.hpp
// Verify: math/bigint-rational.hpp
// 一括includeだけで大きな有理数・二項係数・FPSを実際に計算し、既知の分数やPascalの漸化式と比較する。
#include <bits/stdc++.h>
using namespace std;
#include "math/bigint-all.hpp"

int main() {
  bigint d(
      string("115792089237316195423570985008687907853269984665640564039457584007913129639936"));
  bigint half(
      string("57896044618658097711785492504343953926634992332820282019728792003956564819968"));
  BigRational a(bigint(1), d);
  // 1/2^256を2回足すと1/2^255になり、大きな分母の約分を確認できる。
  assert(a + a == BigRational(bigint(1), half));
  // 分子・分母がどちらも機械整数を超えても、共通因子を正確に除ける。
  assert(BigRational(d * 7, d * 15) == BigRational(7, 15));
  // 大きな分子・分母の浮動小数点変換を、既知の2の冪と比較する。
  assert(abs(to_double(a) / ldexp(1.0, -256) - 1.0) < 1e-14);

  Binomial_rational<BigRational> bin;
  vector<bigint> row(101);
  row[0] = 1;
  for (int n = 0; n <= 100; ++n) {
    for (int r = 0; r <= n; ++r) {
      // 階乗・逆元を使う二項係数を、加算だけで作ったPascalの行と比較する。
      assert(bin.C(n, r) == BigRational(row[r]));
    }
    for (int r = n + 1; r > 0; --r) {
      if (r <= 100) {
        row[r] += row[r - 1];
      }
    }
  }
  using F = FormalPowerSeries_rational<BigRational>;
  auto geometric = F{1, -1}.inv(20);
  for (int i = 0; i < 20; ++i) {
    // 一括includeから使う大きな有理数FPSでも、1/(1-x)の係数は全て1になる。
    assert(geometric[i] == BigRational(1));
  }
}
