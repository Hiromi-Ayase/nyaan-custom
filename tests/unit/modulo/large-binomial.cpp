// Verify: modulo/arbitrary-mod-binomial-large.hpp
// 小さいnはPascalの三角形、大きいnは整数の因子を約分した積で照合し、SIMD経路も実行する。
#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;
#include "modulo/arbitrary-mod-binomial-large.hpp"

long long choose_small_k(long long n, int k, long long mod) {
  if (k < 0 || n < k) {
    return 0;
  }
  vector<unsigned long long> numerator(k);
  for (int i = 0; i < k; ++i) {
    numerator[i] = n - i;
  }
  for (unsigned long long d = 1; d <= (unsigned)k; ++d) {
    auto remaining = d;
    for (auto& factor : numerator) {
      auto g = gcd(factor, remaining);
      factor /= g;
      remaining /= g;
    }
    // 二項係数は整数なので、全分母を分子の因子だけで消去できる。
    assert(remaining == 1);
  }
  long long result = 1 % mod;
  for (auto factor : numerator) {
    result = (__uint128_t)result * factor % mod;
  }
  return result;
}

int main() {
  int large_prime = 20000000;
  while (true) {
    bool prime = true;
    for (int d = 2; 1LL * d * d <= large_prime; ++d) {
      if (large_prime % d == 0) {
        prime = false;
        break;
      }
    }
    if (prime) {
      break;
    }
    ++large_prime;
  }
  for (int mod : {1, 2, 4, 8, 9, 27, 32, 64, 72, 100, 121, 343, 1009, large_prime}) {
    arbitrary_mod_binomial binomial(mod);
    vector<vector<long long>> pascal(201, vector<long long>(201));
    pascal[0][0] = 1 % mod;
    for (int n = 1; n <= 200; ++n) {
      pascal[n][0] = 1 % mod;
      for (int k = 1; k <= n; ++k) {
        pascal[n][k] = (pascal[n - 1][k - 1] + pascal[n - 1][k]) % mod;
      }
    }
    for (int n = 0; n <= 200; ++n) {
      for (int k = -1; k <= n + 1; ++k) {
        // 合成数・素数冪・法1でも逆元を使わないPascal表と一致する。
        assert(binomial.C(n, k) == (k < 0 || k > n ? 0 : pascal[n][k]));
      }
    }
    for (long long n : {1000000LL, 1000000000000000000LL, (long long)large_prime - 1,
                        (long long)large_prime, (long long)large_prime + 1}) {
      for (int k = 0; k <= 20; ++k) {
        // 10^18付近や素数を跨ぐ場合も、整数で約分した積と比較する。
        assert(binomial.C(n, k) == choose_small_k(n, k, mod));
      }
    }
  }
}
