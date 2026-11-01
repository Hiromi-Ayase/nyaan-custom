// Verify: modulo/binomial.hpp
// Verify: modulo/binomial-table.hpp
// Verify: modulo/fastpow.hpp
// 整数のPascal三角形を法で割った値と二項係数を比較する。階乗・順列・重複組合せも直接計算する。
// 遅延拡張、範囲外r、0!、法直前までの係数、FastPowのテーブル切替位置を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "modulo/binomial.hpp"
#include "modulo/binomial-table.hpp"
#include "modulo/fastpow.hpp"

int main() {
  using M = ModInt<101>;
  Binomial<M> bin;
  auto table = binomial_table<M>(100);
  vector<vector<int>> pascal(101, vector<int>(101));
  pascal[0][0] = 1;
  for (int n = 1; n <= 100; ++n) {
    for (int r = 0; r <= n; ++r) {
      pascal[n][r] = ((r ? pascal[n - 1][r - 1] : 0) + pascal[n - 1][r]) % 101;
    }
  }

  int fac = 1;
  for (int n = 0; n <= 100; ++n) {
    if (n) {
      fac = fac * n % 101;
    }

    // 階乗は順に掛けた積と一致し、階乗逆元を掛けると1になる。
    assert(bin.fac(n).get() == fac && (bin.finv(n) * fac).get() == 1);
    for (int r = -1; r <= n + 1; ++r) {
      int expected = r < 0 || r > n ? 0 : pascal[n][r];

      // 通常版と逐次計算版の二項係数を、Pascalの漸化式で作った期待値と比較する。
      assert(bin.C(n, r).get() == expected && bin.C_naive(n, r).get() == expected);
      if (r >= 0 && r <= n) {
        // 前計算した二項係数テーブルも、Pascalの漸化式の値と一致する。
        assert(table[n][r].get() == expected);
      }

      int p = 1;
      if (r < 0 || r > n) {
        p = 0;
      } else {
        for (int i = 0; i < r; ++i) {
          p = p * (n - i) % 101;
        }
      }

      // 順列の個数をnからr個の整数を掛けた値と比べ、不正なrで0になることも確認する。
      assert(bin.P(n, r).get() == p);
    }
  }

  for (int a = 0; a < 101; ++a) {
    FastPow<M, 3> power{M(a)};
    int expected = 1;
    for (int e = 0; e < 512; ++e) {
      // 前計算する冪テーブルを、底を1回ずつ掛けた値と指数ごとに照合する。
      assert(power(e).get() == expected);
      expected = expected * a % 101;
    }
  }
}
