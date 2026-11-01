// Verify: math-fast/binary-search.hpp
// Verify: math-fast/gcd.hpp
// Verify: math-fast/inv.hpp
// Verify: math-fast/inv-o1.hpp
// Verify: math-fast/radix-sort.hpp
// 二分探索とソートは標準ライブラリ、GCDは剰余Euclid、逆元は全探索または乗算検算と比較する。
// 空配列・重複・符号付き整数の両端・ソート方式が切り替わる64前後・128bit GCDを検証する。
#include <bits/stdc++.h>
using namespace std;
#include "math-fast/binary-search.hpp"
#include "math-fast/gcd.hpp"
#include "math-fast/inv.hpp"
#include "math-fast/inv-o1.hpp"
#include "math-fast/radix-sort.hpp"

template <class T>
void sorting() {
  mt19937_64 rng(618);
  for (int n : {0, 1, 2, 63, 64, 65, 1000, 4097}) {
    vector<T> a(n);
    for (auto& x : a) {
      x = T(rng());
    }

    if (n) {
      a[0] = numeric_limits<T>::min();
    }

    if (n > 1) {
      a[1] = numeric_limits<T>::max();
    }

    auto expected = a;
    sort(expected.begin(), expected.end());
    radix_sort(a);

    // 符号付き・符号なし各型のradix sortが、標準sortと同じ昇順になる。
    assert(a == expected);
    for (int q = 0; q < 100; ++q) {
      T x = q < n ? a[q] : T(rng());

      // 最初の「x以上」の位置が、標準lower_boundと一致する。
      assert(fast_lb(a, x) == lower_bound(a.begin(), a.end(), x) - a.begin());

      // 最初の「xより大きい」位置が、標準upper_boundと一致する。
      assert(fast_ub(a, x) == upper_bound(a.begin(), a.end(), x) - a.begin());
    }

    vector<pair<T, int>> pairs(n);
    for (int i = 0; i < n; ++i) {
      pairs[i] = {T(int(rng() % 31) - 15), i};
    }

    auto ep = pairs;
    stable_sort(ep.begin(), ep.end(), [](auto x, auto y) { return x.first < y.first; });
    radix_sort_compare_first(n, pairs.data());

    // 第1要素でのソート結果が、同じ値の元の順序も含めてstable_sortと一致する。
    assert(pairs == ep);
  }
}

int main() {
  sorting<int>();
  sorting<unsigned>();
  sorting<long long>();
  sorting<unsigned long long>();
  mt19937_64 rng(325);
  for (int i = 0; i < 10000; ++i) {
    long long a = rng() >> 1;
    long long b = rng() >> 1;
    if (i % 7 == 0) {
      a = 0;
    }

    if (i % 2) {
      a = -a;
    }

    if (i % 3) {
      b = -b;
    }

    // 64bitのbinary gcdを標準gcdと比較する。0や符号反転した入力も含める。
    assert(binary_gcd(a, b) == gcd(a, b));
    __int128 x = (__int128)a * (1LL << 45);
    __int128 y = (__int128)b * (1LL << 37);
    __int128 u = x < 0 ? -x : x;
    __int128 v = y < 0 ? -y : y;
    while (v) {
      auto r = u % v;
      u = v;
      v = r;
    }

    // 128bitのbinary gcdを、剰余演算によるEuclidの互除法と比較する。
    assert(binary_gcd128(x, y) == u);
  }

  fast_modinv<105> composite;
  for (int a = 1; a < 105; ++a) {
    if (gcd(a, 105) == 1) {
      int expected = 1;
      while (a * expected % 105 != 1) {
        ++expected;
      }

      // 合成数の法でも、逆元が存在する値について全剰余探索で見つけた逆元と一致する。
      assert(composite(a) == (unsigned)expected);
    }
  }

  fast_modinv<10007> fast;
  Inverse_O1<10007> table;
  for (int a = 1; a < 10007; ++a) {
    // 前計算の少ない逆元計算でも、元の値との積の剰余は1になる。
    assert(1LL * a * fast(a) % 10007 == 1);

    // 定数時間の逆元テーブルでも、元の値との積の剰余は1になる。
    assert(1LL * a * table(a) % 10007 == 1);
  }
}
