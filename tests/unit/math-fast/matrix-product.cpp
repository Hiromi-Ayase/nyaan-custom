// Verify: math-fast/mat-prod-strassen.hpp
// 固定サイズ1024の行列に、各行3要素だけを持つ左行列を掛け、全出力を3項の直接和と比較する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modint/montgomery-modint.hpp"
#include "math-fast/mat-prod-strassen.hpp"

int main() {
  using M = LazyMontgomeryModInt<998244353>;
  mmint::set_mod<M>();
  constexpr int n = fast_mat_prod_impl::S;
  alignas(32) static unsigned a[n * n];
  alignas(32) static unsigned b[n * n];
  alignas(32) static unsigned c[n * n];
  mt19937 rng(612);
  for (auto& x : b) {
    x = rng() % M::get_mod();
  }
  for (int trial = 0; trial < 2; ++trial) {
    fill(begin(a), end(a), 0);
    for (int i = 0; i < n; ++i) {
      a[i * n + i] = trial ? M::get_mod() - 1 : 1;
      a[i * n + (i + 127) % n] = 3;
      a[i * n + (i + 513) % n] = 7;
    }
    fast_mat_prod_impl::prod(a, b, c);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        unsigned long long expected = 0;
        for (int offset : {0, 127, 513}) {
          int k = (i + offset) % n;
          expected = (expected + (unsigned long long)a[i * n + k] * b[k * n + j]) % M::get_mod();
        }
        // ブロック境界をまたぐ3行の重み付き和になり、通常の剰余表現で返る。
        assert(c[i * n + j] == expected);
      }
    }
  }
}
