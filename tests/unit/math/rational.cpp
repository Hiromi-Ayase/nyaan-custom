// Verify: math/rational.hpp
// Verify: math/rational-binomial.hpp
// Verify: math/float-binomial.hpp
// 有理数の演算を整数の交差積とgcdで検証し、組合せ・順列は小さい整数の直接計算と比較する。
#include <bits/stdc++.h>
using namespace std;
#include "math/rational.hpp"
#include "math/rational-binomial.hpp"
#include "math/float-binomial.hpp"

void check(Rational actual, long long numerator, long long denominator) {
  // 計算結果は分母が正の既約分数で、期待する整数比と交差積が等しい。
  assert(actual.y > 0 && gcd(actual.x, actual.y) == 1);
  assert((__int128)actual.x * denominator == (__int128)numerator * actual.y);
}

int main() {
  mt19937 rng(711);
  for (int trial = 0; trial < 20000; ++trial) {
    long long a = int(rng() % 61) - 30;
    long long b = 1 + rng() % 20;
    long long c = int(rng() % 61) - 30;
    long long d = 1 + rng() % 20;
    if (trial % 2) {
      b = -b;
    }
    Rational x(a, b);
    Rational y(c, d);
    check(x, a, b);
    check(x + y, a * d + b * c, b * d);
    check(x - y, a * d - b * c, b * d);
    check(x * y, a * c, b * d);
    check(-x, -a, b);
    if (c != 0) {
      check(x / y, a * d, b * c);
      check(y.inverse(), d, c);
    }
    bool less = b > 0 ? a * d < c * b : a * d > c * b;
    // 分母の符号も考慮した交差積による順序と、比較演算子の結果が一致する。
    assert((x < y) == less);
    // 約分前の表現が異なっても、同じ値なら等しいと判定する。
    assert((x == y) == (a * d == b * c));
    long long numerator = 1;
    long long denominator = 1;
    for (int k = 0; k <= 4; ++k) {
      check(x.pow(k), numerator, denominator);
      numerator *= a;
      denominator *= b;
    }
  }
  Binomial_rational<> bin;
  FloatBinomial floating(100);
  vector<vector<long long>> pascal(13, vector<long long>(13));
  pascal[0][0] = 1;
  for (int n = 1; n <= 12; ++n) {
    for (int r = 0; r <= n; ++r) {
      pascal[n][r] = (r ? pascal[n - 1][r - 1] : 0) + pascal[n - 1][r];
    }
  }
  long long factorial = 1;
  for (int n = 0; n <= 12; ++n) {
    if (n) {
      factorial *= n;
    }
    check(bin.fac(n), factorial, 1);
    check(bin.finv(n), 1, factorial);
    // 対数で保持する階乗を、整数の階乗の対数と比較する。
    assert(abs(floating.logfac(n) - logl(factorial)) < 1e-12L);
    for (int r = -1; r <= n + 1; ++r) {
      long long combinations = r < 0 || r > n ? 0 : pascal[n][r];
      check(bin.C(n, r), combinations, 1);
      long long permutations = r < 0 || r > n ? 0 : 1;
      for (int i = 0; i < r && r <= n; ++i) {
        permutations *= n - i;
      }
      check(bin.P(n, r), permutations, 1);
      // 範囲外のrはLOGZERO、それ以外は整数として数えた組合せ・順列の対数を返す。
      assert(abs(floating.logC(n, r) -
                 (combinations ? logl(combinations) : FloatBinomial::LOGZERO)) < 1e-12L);
      assert(abs(floating.logP(n, r) -
                 (permutations ? logl(permutations) : FloatBinomial::LOGZERO)) < 1e-12L);
    }
  }
  for (int a = 0; a <= 3; ++a) {
    for (int b = 0; b <= 3; ++b) {
      for (int c = 0; c <= 3; ++c) {
        long long expected = pascal[a + b + c][a] * pascal[b + c][b];
        check(bin.multinomial(vector{a, b, c}), expected, 1);
      }
    }
  }
  for (int n = 0; n <= 6; ++n) {
    for (int r = 0; r <= 6; ++r) {
      vector<long long> dp(r + 1);
      dp[0] = 1;
      for (int type = 0; type < n; ++type) {
        for (int count = 1; count <= r; ++count) {
          dp[count] += dp[count - 1];
        }
      }
      // n種類から重複を許してr個選ぶ方法を、種類ごとの個数を足すDPで数える。
      check(bin.H(n, r), dp[r], 1);
    }
  }
}
