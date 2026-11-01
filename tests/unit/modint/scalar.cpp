// Verify: modint/modint.hpp
// Verify: modint/montgomery-modint.hpp
// Verify: modint/arbitrary-modint.hpp
// Verify: modint/arbitrary-montgomery-modint.hpp
// Verify: modint/modint-cpp11.hpp
// Verify: modint/modint-2-61m1.hpp
// 整数の128bit演算と剰余を期待値として、構築・四則演算・符号反転・累乗を比較する。
// 0、±1、法の前後、負数、大きな64bit入力、動的な法の切替と合成数の可逆元を検証する。
// 期待する逆元はテスト内の拡張Euclidで独立に計算する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "modint/montgomery-modint.hpp"
#include "modint/arbitrary-modint.hpp"
#include "modint/arbitrary-montgomery-modint.hpp"
#include "modint/modint-cpp11.hpp"
#include "modint/modint-2-61m1.hpp"

template <class M>
void test() {
  long long mod = M::get_mod();
  auto norm = [=](__int128 x) {
    x %= mod;
    if (x < 0) {
      x += mod;
    }

    return (long long)x;
  };
  auto inverse = [&](long long b) {
    __int128 a = b;
    __int128 c = mod;
    __int128 x = 1;
    __int128 y = 0;
    while (c) {
      auto q = a / c;
      auto r = a - q * c;
      a = c;
      c = r;
      auto z = x - q * y;
      x = y;
      y = z;
    }

    return norm(x);
  };
  vector<long long> cases{0, 1, -1, mod - 1, mod, mod + 1, -mod, LLONG_MAX, LLONG_MIN + 1};
  mt19937_64 rng(834);
  for (int i = 0; i < 300; ++i) {
    cases.push_back((long long)(rng() >> 1) * (i % 2 ? -1 : 1));
  }

  for (long long a : cases) {
    M x(a);

    // 負数や整数上限に近い値の構築結果を、128bit整数で正規化した剰余と比較する。
    assert(x.get() == norm(a));

    // 単項マイナスを、128bit整数で符号反転してから正規化した値と比較する。
    assert((-x).get() == norm(-(__int128)a));
    for (int q = 0; q < 8; ++q) {
      long long b = cases[rng() % cases.size()];
      M y(b);

      // 加算が整数の桁あふれに影響されず、128bitで計算した剰余と一致する。
      assert((x + y).get() == norm((__int128)a + b));

      // 減算後の負の値も、0以上かつ法未満の代表元として取得できる。
      assert((x - y).get() == norm((__int128)a - b));

      // 乗算を128bitの積の剰余と比較し、境界値でも桁あふれの影響がないか確認する。
      assert((x * y).get() == norm((__int128)norm(a) * norm(b)));
      if (norm(b) && gcd(norm(b), mod) == 1) {
        // 除算は、拡張Euclid法で独立に求めた逆元を掛けた結果と一致する。
        assert((x / y).get() == norm((__int128)norm(a) * inverse(norm(b))));
      }
    }

    long long expected = 1 % mod;
    for (int e = 0; e <= 24; ++e) {
      // 冪の結果を、底を1回ずつ掛けた剰余と指数ごとに比較する。
      assert(x.pow(e).get() == expected);
      expected = norm((__int128)expected * norm(a));
    }
  }
}

int main() {
  test<ModInt<2>>();
  test<ModInt<15>>();
  test<ModInt<998244353>>();
  test<LazyMontgomeryModInt<3>>();
  test<LazyMontgomeryModInt<998244353>>();
  test<MontgomeryModInt998244353>();
  test<modint_2_61m1>();
  for (int p : {2, 15, 17, 1000000007}) {
    ArbitraryModInt::set_mod(p);
    test<ArbitraryModInt>();
  }

  for (int p : {3, 15, 17, 998244353}) {
    ArbitraryLazyMontgomeryModInt<812>::set_mod(p);
    test<ArbitraryLazyMontgomeryModInt<812>>();
  }

  for (long long p : {3LL, 1000000007LL, (1LL << 61) - 1}) {
    ArbitraryLazyMontgomeryModInt64bit<813>::set_mod(p);
    test<ArbitraryLazyMontgomeryModInt64bit<813>>();
  }
}
