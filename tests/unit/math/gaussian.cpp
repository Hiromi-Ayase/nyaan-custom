// Verify: math/gaussian-integer.hpp
// Verify: math/two-square.hpp
// Gaussian整数の積・商・GCDを成分の整数計算で照合し、二平方和の全解を座標の全列挙と比較する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/gaussian-integer.hpp"
#include "math/two-square.hpp"

using G = Gaussian_Integer<long long>;

bool divides_exactly(G a, G divisor) {
  long long norm = divisor.x * divisor.x + divisor.y * divisor.y;
  if (!norm) {
    return a.x == 0 && a.y == 0;
  }
  return (a.x * divisor.x + a.y * divisor.y) % norm == 0 &&
         (a.y * divisor.x - a.x * divisor.y) % norm == 0;
}

int main() {
  mt19937 rng(731);
  for (int trial = 0; trial < 3000; ++trial) {
    long long ax = int(rng() % 11) - 5;
    long long ay = int(rng() % 11) - 5;
    long long bx = int(rng() % 11) - 5;
    long long by = int(rng() % 11) - 5;
    G a(pair{ax, ay});
    G b(bx, by);
    // pairからの構築で、実部・虚部の順序が保存される。
    assert(a.x == ax && a.y == ay);
    // 複素数の積を成分ごとに直接展開した値と比較する。
    assert(a * b == G(ax * bx - ay * by, ax * by + ay * bx));
    // 共役との積は実数のnormとなり、虚部は0になる。
    assert(a * a.conj() == G(ax * ax + ay * ay, 0));
    if (b != G()) {
      auto quotient = a / b;
      auto remainder = a % b;
      // 商と余りはa=q*b+rを満たし、余りのnormが除数より小さい。
      assert(quotient * b + remainder == a && remainder.norm() < b.norm());
    }
    auto common = gcd(a, b);
    long long expected_norm = 0;
    if (a != G() || b != G()) {
      for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
          G candidate(x, y);
          if (candidate != G() && divides_exactly(a, candidate) && divides_exactly(b, candidate)) {
            expected_norm = max(expected_norm, candidate.norm());
          }
        }
      }
    }
    // GCDは単数倍の自由度があるため、全共通約数の最大normと割り切れで比較する。
    assert(common.norm() == expected_norm && divides_exactly(a, common) &&
           divides_exactly(b, common));
    G power(1);
    for (int k = 0; k <= 6; ++k) {
      // 冪を1回ずつ掛けた結果と比較し、指数0も確認する。
      assert(a.pow(k) == power);
      power *= a;
    }
  }
  for (long long n = -2; n <= 3000; ++n) {
    vector<pair<long long, long long>> expected;
    for (long long x = 0; x * x <= n; ++x) {
      for (long long y = 0; x * x + y * y <= n; ++y) {
        if (x * x + y * y == n) {
          expected.emplace_back(x, y);
        }
      }
    }
    // 両座標が非負の解を直接列挙し、負数・0・完全平方数・複数解も順序まで比較する。
    assert(two_square(n) == expected);
  }
}
