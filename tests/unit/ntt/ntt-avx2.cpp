// Verify: ntt/ntt-avx2.hpp
// 全係数を二重ループの整数積と比較する。法-1、0、平方、切替閾値と2冪境界を含める。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "ntt/ntt-avx2.hpp"

int main() {
  using M = LazyMontgomeryModInt<998244353>;

  NTT<M> ntt;
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
