// Verify: ntt/arbitrary-ntt.hpp
// 合成数を含む法でCRT畳み込みを直接計算と比較し、128bit整数版も切替閾値の前後で照合する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/arbitrary-modint.hpp"
#include "ntt/arbitrary-ntt.hpp"

int main() {
  using M = ArbitraryModIntBase<951>;
  mt19937 rng(9042);
  for (int mod : {2, 6, 101, 998244353, 1000000007}) {
    M::set_mod(mod);
    for (int n : {1, 39, 40, 41, 127, 128, 129, 257}) {
      for (int m : {1, 41, 128, 255}) {
        vector<int> a(n);
        vector<int> b(m);
        vector<M> ma(n);
        vector<M> mb(m);
        for (int i = 0; i < n; ++i) {
          a[i] = rng() % mod;
          ma[i] = a[i];
        }
        for (int j = 0; j < m; ++j) {
          b[j] = rng() % mod;
          mb[j] = b[j];
        }
        vector<__uint128_t> exact(n + m - 1);
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < m; ++j) {
            exact[i + j] += (__uint128_t)a[i] * b[j];
          }
        }
        vector<int> expected(n + m - 1);
        for (int k = 0; k < (int)exact.size(); ++k) {
          expected[k] = exact[k] % mod;
        }
        // 整数入力版は、通常の128bit畳み込みに最後に剰余を取った値と一致する。
        assert(ArbitraryNTT::multiply(a, b, mod) == expected);

        // 128bit版は、CRTで復元可能な範囲の非負整数の積を正確に返す。
        assert(ArbitraryNTT::multiply_u128(a, b) == exact);
        auto got = ArbitraryNTT::multiply(ma, mb);
        for (int k = 0; k < (int)expected.size(); ++k) {
          // modint入力版の高速経路・素朴な経路も、独立した整数計算と一致する。
          assert(got[k].get() == expected[k]);
        }
      }
    }
  }
}
