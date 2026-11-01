// Verify: modulo/mod-sqrt.hpp
// Verify: modulo/mod-kth-root.hpp
// Verify: modulo/quadratic-equation.hpp
// 小さい素数法の全剰余を代入して、平方根・k乗根・二次方程式の解集合を求める。
// 解なし、重根、判別式の平方根1、線形方程式、指数0を含める。無限個の解を持つ恒等式はAPI対象外。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modint/arbitrary-modint.hpp"
#include "modulo/mod-sqrt.hpp"
#include "modulo/mod-kth-root.hpp"
#include "modulo/quadratic-equation.hpp"

int main() {
  using M = ArbitraryModIntBase<1991>;
  for (int p : {3, 5, 7, 17, 31, 97}) {
    M::set_mod(p);
    for (int a = 0; a < p; ++a) {
      bool exists = false;
      for (int x = 0; x < p; ++x) {
        exists |= x * x % p == a;
      }

      long long root = mod_sqrt(a, p);

      // 全剰余を2乗して調べた解の存在と一致し、解がない場合は-1を返す。
      assert((root != -1) == exists);
      if (exists) {
        // 返された平方根を2乗すると、元の剰余aに戻る。
        assert(root * root % p == a);
      }

      for (int k = 0; k <= 12; ++k) {
        exists = false;
        for (int x = 0; x < p; ++x) {
          int y = 1;
          for (int i = 0; i < k; ++i) {
            y = y * x % p;
          }

          exists |= y == a;
        }

        long long r = kth_root(a, k, p);

        // 全剰余をk乗して調べた解の存在と一致し、存在しない場合は-1を返す。
        assert((r != -1) == exists);
        if (exists) {
          long long y = 1;
          for (int i = 0; i < k; ++i) {
            y = y * r % p;
          }

          // 返されたk乗根を逐次乗算でk乗すると、元の剰余aに戻る。
          assert(y == a);
        }
      }
    }

    // 二次方程式は法17以下を全探索し、それ以上は固定シードでサンプルする。
    mt19937 rng(638);
    int cases = p <= 17 ? p * p * p : 2000;
    for (int i = 1; i < cases; ++i) {
      int a = p <= 17 ? i / (p * p) : rng() % p;
      int b = p <= 17 ? i / p % p : rng() % p;
      int c = p <= 17 ? i % p : rng() % p;
      if (a == 0 && b == 0 && c == 0) {
        continue;
      }

      vector<int> expected;
      for (int x = 0; x < p; ++x) {
        if ((a * x * x + b * x + c) % p == 0) {
          expected.push_back(x);
        }
      }

      vector<int> got;
      for (auto x : QuadraticEquation(M(a), M(b), M(c))) {
        got.push_back(x.get());
      }

      sort(got.begin(), got.end());

      // 全剰余を二次方程式へ代入して列挙した解集合と比較し、解の欠落や重複を検出する。
      assert(got == expected);
    }
  }
}
