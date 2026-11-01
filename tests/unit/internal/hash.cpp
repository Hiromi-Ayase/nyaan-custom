// Verify: internal/internal-hash.hpp
// Verify: internal/internal-hash-function.hpp
// Verify: internal/internal-seed.hpp
// 61bit剰余の各レーンを128bit整数演算と照合し、積和と累乗を検証する。
// 汎用ハッシュは等しいキーの一貫性とunordered_mapでの検索を確認する。ローカル用シードの固定性も確認する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "internal/internal-hash.hpp"
#include "internal/internal-hash-function.hpp"
#include "internal/internal-seed.hpp"

int main() {
  using H = internal::Hash<3>;
  mt19937_64 rng(212);
  const unsigned long long mod = (1ULL << 61) - 1;
  for (int t = 0; t < 10000; ++t) {
    H a;
    H b;
    H c;
    for (int i = 0; i < 3; ++i) {
      a[i] = rng() % mod;
      b[i] = rng() % mod;
      c[i] = rng() % mod;
    }

    auto s = a + b;
    auto d = a - b;
    auto p = a * b;
    auto f = pfma(a, b, c);
    auto neg = -a;
    for (int i = 0; i < 3; ++i) {
      // ハッシュの各成分の和を、通常の剰余演算と比較する。
      assert(s[i] == (a[i] + b[i]) % mod);

      // 各成分の差を、法を加えて非負にした剰余と比較する。
      assert(d[i] == (a[i] + mod - b[i]) % mod);

      // 各成分の積を128bit整数で計算し、特殊な剰余計算と照合する。
      assert(p[i] == (__uint128_t)a[i] * b[i] % mod);

      // 積和演算を、128bit整数で積と加算を行ってから剰余を取った値と比較する。
      assert(f[i] == ((__uint128_t)a[i] * b[i] + c[i]) % mod);

      // 単項マイナスが、法を基準にした加法逆元になる。
      assert(neg[i] == (mod - a[i]) % mod);
    }

    if (t < 100) {
      for (int e = 0; e < 20; ++e) {
        auto power = a.pow(e);
        for (int i = 0; i < 3; ++i) {
          unsigned long long expected = 1;
          for (int j = 0; j < e; ++j) {
            expected = (__uint128_t)expected * a[i] % mod;
          }

          // 各成分の冪を、1回ずつ掛けた剰余と比較する。
          assert(power[i] == expected);
        }
      }
    }
  }

  // ローカル設定の乱数種が既定の固定値であり、再実行可能な入力を作れる。
  assert(internal::seed() == 88172645463325252ULL);
  for (int i = 0; i < 100; ++i) {
    // ローカル設定では、通常のseed取得も決定的なseedを使う。
    assert(internal::seed() == internal::deterministic_seed());
  }

  unordered_map<vector<int>, int, internal::HashObject<vector<int>>> map;
  vector<vector<int>> keys{{}, {0}, {1}, {-1}, {1, 2}, {2, 1}, {0, 0}, {INT_MIN, INT_MAX}};
  for (int i = 0; i < (int)keys.size(); ++i) {
    map[keys[i]] = i;
  }

  for (int i = 0; i < (int)keys.size(); ++i) {
    auto copy = keys[i];

    // 同じ内容をコピーしたキーで、unordered_mapに保存した値を取得できる。
    assert(map.at(copy) == i);

    // 同じ内容のキーが、オブジェクトの所在によらず同じハッシュ値になる。
    assert(internal::hash_function(copy) == internal::hash_function(keys[i]));
  }
}
