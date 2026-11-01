// Verify: math/semiring.hpp
// Verify: math/semiring-linear-recursive.hpp
// min-plus半環の単位元・吸収元を含む演算、固定サイズ行列の冪、線形漸化式を直接DPと比較する。
#include <bits/stdc++.h>
using namespace std;
#include "math/semiring.hpp"
#include "math/semiring-linear-recursive.hpp"

constexpr long long inf = 1000000000000LL;

long long add(long long a, long long b) {
  return min(a, b);
}

long long mul(long long a, long long b) {
  return a + b;
}

long long zero() {
  return inf;
}

long long one() {
  return 0;
}

using R = semiring<long long, add, mul, zero, one>;

int main() {
  mt19937 rng(713);
  for (long long a : {-7LL, 0LL, 8LL, inf}) {
    for (long long b : {-5LL, 0LL, 9LL, inf}) {
      // min-plusの和はminであり、加法単位元のINFも通常の最小値として扱える。
      assert((R(a) + R(b)).x == min(a, b));
      // 積は通常の加算だが、到達不能を表すINFは吸収元になる。
      assert((R(a) * R(b)).x == (a == inf || b == inf ? inf : a + b));
    }
  }
  for (int trial = 0; trial < 100; ++trial) {
    Mat<R, 3> a;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        a[i][j] = rng() % 4 == 0 ? inf : int(rng() % 21) - 10;
      }
    }
    vector<vector<long long>> dp(3, vector<long long>(3, inf));
    for (int i = 0; i < 3; ++i) {
      dp[i][i] = 0;
    }
    for (int length = 0; length <= 15; ++length) {
      auto powered = a ^ length;
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          // ちょうどlength本の辺を通る最小コストを、1辺ずつ延ばすDPと比較する。
          assert(powered[i][j].x == dp[i][j]);
        }
      }
      vector<vector<long long>> next(3, vector<long long>(3, inf));
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          for (int k = 0; k < 3; ++k) {
            if (dp[i][k] != inf && a[k][j].x != inf) {
              next[i][j] = min(next[i][j], dp[i][k] + a[k][j].x);
            }
          }
        }
      }
      dp = next;
    }
  }
  for (int n = 1; n <= 7; ++n) {
    vector<R> coefficients(n);
    vector<R> initial(n);
    for (auto& x : coefficients) {
      x = int(rng() % 11) - 5;
    }
    for (auto& x : initial) {
      x = int(rng() % 11) - 5;
    }
    LinearRecursive<R> recurrence(coefficients);
    vector<long long> dp(101, inf);
    for (int i = 0; i < n; ++i) {
      dp[i] = initial[i].x;
    }
    for (int i = n; i <= 100; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[i] = min(dp[i], coefficients[j].x + dp[i - j - 1]);
      }
    }
    for (int k = 0; k <= 100; ++k) {
      // 各項を順番に計算したmin-plus漸化式と、高速なk項目取得の結果が一致する。
      assert(recurrence.kth_term(initial, k).x == dp[k]);
    }
  }
}
