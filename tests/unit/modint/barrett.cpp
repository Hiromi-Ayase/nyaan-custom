// Verify: modint/barrett-reduction.hpp
// 通常の整数除算・剰余とBarrettの商、余り、同時計算を比較する。
// 法1、小さな合成数、大きな法、法の倍数の前後と63bit整数を含む。累乗は繰り返し乗算と照合する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/barrett-reduction.hpp"

int main() {
  mt19937_64 rng(935);
  for (int mod : {1, 2, 3, 4, 15, 65537, 998244353, 2147483647}) {
    Barrett b(mod);
    vector<unsigned long long> values{0,
                                      1,
                                      (unsigned)mod - 1,
                                      (unsigned)mod,
                                      (unsigned)mod + 1,
                                      (unsigned long long)mod * mod - 1,
                                      (unsigned long long)LLONG_MAX};
    for (int i = 0; i < 5000; ++i) {
      values.push_back(rng() >> 1);
    }

    for (auto x : values) {
      // Barrett除算の商を通常の整数除算と比較する。法1と大きな被除数も含める。
      assert(b.quo(x) == (long long)(x / mod));

      // Barrett除算の余りを通常の剰余演算と比較する。
      assert(b.rem(x) == (long long)(x % mod));
      auto [q, r] = b.quorem(x);

      // 商と余りを同時に返すAPIも、それぞれ通常の除算・剰余と一致する。
      assert(q == (long long)(x / mod) && r == (int)(x % mod));
    }

    for (int a = 0; a < 30; ++a) {
      long long expected = 1 % mod;
      for (int e = 0; e < 30; ++e) {
        // 高速な冪剰余を、1回ずつ掛けて剰余を取った値と比較する。
        assert(b.pow(a, e) == expected);
        expected = expected * a % mod;
      }
    }
  }
}
