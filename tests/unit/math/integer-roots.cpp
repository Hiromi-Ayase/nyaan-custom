// Verify: math/isqrt.hpp
// Verify: math/kth-root-integral.hpp
// 整数二分探索を参照に、完全冪の前後、0/1、符号付き・符号なし64bitの最大値を比較する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/isqrt.hpp"
#include "math/kth-root-integral.hpp"

bool at_most(unsigned long long base, int exponent, unsigned long long limit) {
  unsigned long long value = 1;
  for (int i = 0; i < exponent; ++i) {
    if (base != 0 && value > limit / base) {
      return false;
    }
    value *= base;
  }
  return value <= limit;
}

int main() {
  vector<unsigned long long> cases{0,
                                   1,
                                   2,
                                   3,
                                   4,
                                   ULLONG_MAX,
                                   ULLONG_MAX - 1,
                                   (unsigned long long)LLONG_MAX,
                                   (unsigned long long)LLONG_MAX - 1};
  mt19937_64 rng(701);
  for (int trial = 0; trial < 1000; ++trial) {
    cases.push_back(rng());
  }
  for (unsigned long long base :
       {2ULL, 3ULL, 7ULL, 10ULL, 65535ULL, 3037000499ULL, 4294967295ULL}) {
    __uint128_t value = 1;
    for (int k = 1; k <= 64; ++k) {
      value *= base;
      if (value > ULLONG_MAX) {
        break;
      }
      cases.push_back((unsigned long long)value - 1);
      cases.push_back(value);
      if (value < ULLONG_MAX) {
        cases.push_back((unsigned long long)value + 1);
      }
    }
  }
  for (auto value : cases) {
    for (int k = 1; k <= 70; ++k) {
      unsigned long long low = 0;
      unsigned long long high = value;
      while (low < high) {
        unsigned long long mid = low + (high - low) / 2 + (high - low) % 2;
        if (at_most(mid, k, value)) {
          low = mid;
        } else {
          high = mid - 1;
        }
      }
      // 浮動小数点を使わず、積の桁あふれも防いだ二分探索の床k乗根と比較する。
      assert(kth_root_integral(value, k) == low);
      if (k == 2 && value <= (unsigned long long)LLONG_MAX) {
        // 符号付き版の平方根も同じ床値になる。最大値付近の補正時の桁あふれを検出する。
        assert(isqrt(value) == (long long)low);
      }
    }
  }
  for (long long value : {LLONG_MIN, -100LL, -1LL, 0LL}) {
    // 負の値と0に対しては、APIで定義された0を返す。
    assert(isqrt(value) == 0);
  }
}
