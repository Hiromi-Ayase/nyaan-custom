// Verify: internal/internal-math.hpp
// Verify: internal/internal-type-traits.hpp
// CRTの解は最小公倍数未満を全探索し、逆元/GCDと累乗は整数演算で検算する。
// 非互いに素の法、矛盾する合同式、負の剰余、法1を含め、128bit対応型特性もコンパイル時に確認する。
#include <bits/stdc++.h>
using namespace std;
#include "internal/internal-math.hpp"
#include "internal/internal-type-traits.hpp"

// 標準の型特性では扱いが異なる場合がある128bit符号付き整数も、整数として認識する。
static_assert(internal::is_broadly_integral_v<__int128>);

// 128bit符号なし整数も、整数として認識する。
static_assert(internal::is_broadly_integral_v<__uint128_t>);

// 浮動小数点型は整数として扱わない。
static_assert(!internal::is_broadly_integral_v<double>);

// 128bit符号付き整数を、符号付きの型として認識する。
static_assert(internal::is_broadly_signed_v<__int128>);

// 128bit符号なし整数を、符号付きの型と誤認しない。
static_assert(!internal::is_broadly_signed_v<__uint128_t>);

// 128bit符号なし整数を、符号なしの型として認識する。
static_assert(internal::is_broadly_unsigned_v<__uint128_t>);
ENABLE_HAS_TYPE(value_type);
ENABLE_HAS_VAR(value);

struct WithValue {
  static constexpr int value = 3;
};

// value_typeを持つvectorと、持たないintを区別できる。
static_assert(has_value_type_v<vector<int>> && !has_value_type_v<int>);

// 指定したメンバvalueが存在する型と、存在しないintを区別できる。
static_assert(has_value_v<WithValue> && !has_value_v<int>);

int main() {
  for (long long m = 1; m <= 60; ++m) {
    for (long long a = -120; a <= 120; ++a) {
      long long norm = (a % m + m) % m;

      // 負の入力も含め、剰余が0以上かつ法未満に正規化される。
      assert(internal::safe_mod(a, m) == norm);
      auto [g, x] = internal::inv_gcd(a, m);

      // 逆元計算と同時に返されるgcdが、標準gcdと一致する。
      assert(g == gcd(a, m));

      // 返された係数xが、a*x≡gcd(a,m)という合同式を満たす。
      assert((norm * x) % m == g % m);
      if (g == 1) {
        // 互いに素な入力では、逆元だけを返すAPIも同じ係数になる。
        assert(internal::inv(a, m) == x);
      }

      long long expected = 1 % m;
      for (long long e = 0; e < 20; ++e) {
        // 冪剰余を、1回ずつ掛けて剰余を取った値と比較する。
        assert((internal::modpow<long long, long long>(a, e, m) == expected));
        expected = expected * norm % m;
      }
    }
  }

  for (long long m = 1; m <= 20; ++m) {
    for (long long n = 1; n <= 20; ++n) {
      for (long long a = 0; a < m; ++a) {
        for (long long b = 0; b < n; ++b) {
          long long period = lcm(m, n);
          long long expected = -1;
          for (long long x = 0; x < period; ++x) {
            if (x % m == a && x % n == b) {
              expected = x;
              break;
            }
          }

          auto [r, mod] = internal::crt<long long>({a, b}, {m, n});
          if (expected < 0) {
            // 連立合同式に解がない場合、法0によって解なしを表す。
            assert(mod == 0);
          } else {
            // 全剰余の探索で求めた最小非負解と、法の最小公倍数による周期に一致する。
            assert(r == expected && mod == period);
          }
        }
      }
    }
  }
}
