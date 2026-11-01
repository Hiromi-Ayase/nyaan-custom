// Verify: prime/fast-factorize.hpp
// Verify: prime/miller-rabin.hpp
// Verify: prime/osak.hpp
// Verify: prime/factor-enumerate.hpp
// Verify: prime/prime-enumerate.hpp
// Verify: prime/prime-sieve.hpp
// 試し割りで素数判定・最小素因数・素因数分解を求め、全整数1..10000で照合する。
// 約数列挙は直接の割り切れ判定と比較し、0/1、小さな上限、素数冪、既知の擬素数、大きい半素数も確認する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "prime/fast-factorize.hpp"
#include "prime/miller-rabin.hpp"
#include "prime/osak.hpp"
#include "prime/factor-enumerate.hpp"
#include "prime/prime-enumerate.hpp"
#include "prime/prime-sieve.hpp"

int main() {
  auto prime = [](unsigned long long n) {
    if (n < 2) {
      return false;
    }

    for (unsigned long long d = 2; d <= n / d; ++d) {
      if (n % d == 0) {
        return false;
      }
    }

    return true;
  };
  for (int limit : {0, 1, 2, 3, 4, 31, 32, 33, 10000}) {
    auto lp = factor_enumerate(limit);
    auto sieve = prime_sieve(limit);
    auto ps = prime_enumerate(limit);
    vector<int> expected;
    for (int n = 0; n <= limit; ++n) {
      bool p = prime(n);

      // 各整数の素数フラグを、平方根までの試し割り判定と比較する。
      assert(sieve[n] == p);
      if (p) {
        expected.push_back(n);
      }

      int first = 0;
      for (int d = 2; d <= n; ++d) {
        if (n % d == 0) {
          first = d;
          break;
        }
      }

      // 最小素因数テーブルを、2から順に試し割りして最初に見つけた約数と比較する。
      assert(lp[n] == first);
    }

    // 素数列の順序と内容が、全整数を試し割りで判定して作った列と一致する。
    assert(ps == expected);
  }

  for (int n = 1; n <= 10000; ++n) {
    vector<long long> factors;
    int rem = n;
    for (int d = 2; d <= rem / d; ++d) {
      while (rem % d == 0) {
        factors.push_back(d);
        rem /= d;
      }
    }

    if (rem > 1) {
      factors.push_back(rem);
    }

    // 通常の素数判定を、小さい整数について独立した試し割り判定と比較する。
    assert(is_prime(n) == prime(n));

    // 64bit用Miller-Rabinの直接呼出しでも、試し割りの判定と一致する。
    assert(fast_factorize::miller_rabin_u64(n) == prime(n));

    // 素因数分解の結果を、同じ素数で繰り返し割った素因数列と比較する。
    assert(factorize(n) == factors);
    vector<int> small(factors.begin(), factors.end());

    // 小さい整数向けの前計算版も、試し割りした素因数列と一致する。
    assert(osak<10000>(n) == small);
    map<long long, long long> counts;
    for (auto p : factors) {
      ++counts[p];
    }

    // 素因数ごとの指数が、試し割りした列から数えた多重度と一致する。
    assert(factor_count(n) == counts);
    if (n <= 500) {
      vector<long long> ds;
      for (int d = 1; d <= n; ++d) {
        if (n % d == 0) {
          ds.push_back(d);
        }
      }

      // 約数列を、1からnまで割り切れる数を全て集めた昇順の列と比較する。
      assert(divisors(n) == ds);
      vector<int> sd(ds.begin(), ds.end());

      // 前計算を使う約数列挙でも、全探索と同じ約数列になる。
      assert(osak_divisors<10000>(n) == sd);
    }
  }

  for (unsigned long long n : {561ULL, 1105ULL, 1729ULL, 3215031751ULL, 341550071728321ULL}) {
    // Carmichael数や強擬素数の既知例を、素数と誤判定しない。
    assert(!is_prime(n));
  }

  // 64bit上限に近い既知の素数を素数と判定できる。
  assert(is_prime(18446744073709551557ULL));

  // 2^64-1は合成数なので、素数と判定してはならない。
  assert(!is_prime(18446744073709551615ULL));
  vector<long long> expected{1000000007, 1000000009};

  // 大きな2素数の積を、期待する2個の素因数へ分解できる。
  assert(factorize(1000000007ULL * 1000000009ULL) == expected);

  // 1の素因数列と、APIで定義された0の約数列は空になる。
  assert(factorize(1).empty() && divisors(0).empty());
}
