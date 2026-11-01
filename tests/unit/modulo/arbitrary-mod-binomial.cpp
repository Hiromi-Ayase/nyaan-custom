// Verify: modulo/arbitrary-mod-binomial.hpp
// 法が素数とは限らない二項係数を、除算を使わないPascalの漸化式と比較する。
// 法1、素数冪、異なる素因数の積、nが法を超える場合、範囲外rを検証する。
#include <bits/stdc++.h>
using namespace std;
#include "modulo/arbitrary-mod-binomial.hpp"

int main() {
  for (int mod : {1, 2, 3, 4, 8, 9, 12, 25, 27, 72, 100, 101, 1000, 10007}) {
    arbitrary_mod_binomial bin(mod);
    vector<vector<int>> dp(201, vector<int>(201));
    dp[0][0] = 1 % mod;
    for (int n = 1; n <= 200; ++n) {
      for (int r = 0; r <= n; ++r) {
        dp[n][r] = ((r ? dp[n - 1][r - 1] : 0) + dp[n - 1][r]) % mod;
      }
    }

    for (int n = 0; n <= 200; ++n) {
      for (int r = -1; r <= n + 1; ++r) {
        // 合成数の法も含め、除算を使わないPascalの漸化式の結果と比較する。範囲外のrは0になる。
        assert(bin.C(n, r) == (r < 0 || r > n ? 0 : dp[n][r]));
      }
    }
  }
}
