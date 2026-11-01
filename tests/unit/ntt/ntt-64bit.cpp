// Verify: ntt/ntt-64bit.hpp
// 全係数を二重ループの整数積と比較する。法-1、0、平方、切替閾値と2冪境界を含める。
#include <bits/stdc++.h>
using namespace std;
#include "modint/arbitrary-montgomery-modint.hpp"
#include "ntt/ntt-64bit.hpp"

// 小さい法を使い、法が許す最大長まで巡回畳み込みを二重ループと比較する。
template <uint32_t Mod>
void check_max_length() {
  using M = ArbitraryLazyMontgomeryModInt64bit<913>;
  M::set_mod(Mod);
  NTT_64bit<M> transform;
  int maximum = 1 << __builtin_ctz(Mod - 1);
  for (int n = 1; n <= maximum; n *= 2) {
    vector<M> a(n);
    vector<M> b(n);
    for (int i = 0; i < n; ++i) {
      a[i] = (i * 7 + 3) % Mod;
      b[i] = (i * i + 5) % Mod;
    }
    vector<unsigned long long> expected(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int k = (i + j) % n;
        expected[k] = (expected[k] + 1ULL * a[i].get() * b[j].get()) % Mod;
      }
    }
    auto fa = a;
    transform.ntt(fa);
    transform.intt(fa);
    // 最大長でも、回転因子の表を超えて参照せず元の列を復元できる。
    assert(fa == a);
    auto fb = b;
    transform.ntt(fa);
    transform.ntt(fb);
    for (int i = 0; i < n; ++i) {
      fa[i] *= fb[i];
    }
    transform.intt(fa);
    for (int i = 0; i < n; ++i) {
      // 順逆変換で同じ誤りが相殺されないよう、添字を巡回させた直接積とも照合する。
      assert(fa[i].get() == expected[i]);
    }
  }
}

int main() {
  check_max_length<17>();
  check_max_length<353>();
  check_max_length<257>();
  using M = ArbitraryLazyMontgomeryModInt64bit<912>;
  M::set_mod(4179340454199820289ULL);
  NTT_64bit<M> ntt;
  const unsigned long long mod = M::get_mod();
  mt19937_64 rng(8131);
  vector<int> lengths{1, 2, 3, 7, 31, 32, 39, 40, 41, 63, 64, 65, 127, 129, 257};

  // 素朴な乗算への切替前後、2冪の前後、不均等な長さを全組合せで試す。
  for (int n : lengths) {
    for (int m : lengths) {
      vector<M> a(n);
      vector<M> b(m);
      for (int i = 0; i < n; ++i) {
        a[i] = i % 3 == 0 ? mod - 1 : rng() % mod;
      }
      for (int j = 0; j < m; ++j) {
        b[j] = j % 5 == 0 ? 0 : rng() % mod;
      }
      if (n == m) {
        b = a;
      }
      vector<unsigned long long> expected(n + m - 1);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          expected[i + j] = ((__uint128_t)a[i].get() * b[j].get() + expected[i + j]) % mod;
        }
      }
      auto got = ntt.multiply(a, b);

      // 非空多項式の積は、末尾が0でもn+m-1個の係数を返す。
      assert(got.size() == expected.size());
      for (int k = 0; k < (int)expected.size(); ++k) {
        // 全添字対の積を128bit整数で足した係数と照合する。平方の専用分岐も通す。
        assert(got[k].get() == expected[k]);
      }
    }
  }

  for (int n = 1; n <= 512; n *= 2) {
    vector<M> a(n);
    for (auto& x : a) {
      x = rng() % mod;
    }
    auto transformed = a;
    ntt.ntt(transformed);
    ntt.intt(transformed);
    // 直接変換と逆変換のAPIは、正規化も含めて元の係数列を復元する。
    assert(transformed == a);
  }
}
