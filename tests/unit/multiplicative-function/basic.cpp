// Verify: multiplicative-function/mf-famous-series.hpp
// Verify: multiplicative-function/enamurate-multiplicative-function.hpp
// Verify: multiplicative-function/count-square-free.hpp
// Verify: multiplicative-function/sum-of-totient.hpp
// Verify: multiplicative-function/divisor-multiple-transform.hpp
// Verify: multiplicative-function/gcd-convolution.hpp
// 乗法的関数は試し割り・約数の直接列挙・互いに素の個数から期待値を求める。
// 無平方数とφの累積和、約数/倍数変換と逆変換、GCD畳み込みを愚直計算と比較する。
#include <bits/stdc++.h>
using namespace std;
#include "multiplicative-function/mf-famous-series.hpp"
#include "multiplicative-function/enamurate-multiplicative-function.hpp"
#include "multiplicative-function/count-square-free.hpp"
#include "multiplicative-function/sum-of-totient.hpp"
#include "multiplicative-function/divisor-multiple-transform.hpp"
#include "multiplicative-function/gcd-convolution.hpp"

long long divisor_cube(int, int, int e) {
  return 3 * e + 1;
}

int main() {
  const int limit = 1000;
  auto mu = mobius_function<long long>(limit);
  auto s0 = sigma0<long long>(limit);
  auto s1 = sigma1<long long>(limit);
  auto phi = totient<long long>(limit);
  enamurate_multiplicative_function<long long, divisor_cube> custom(limit);
  auto cube = custom.run();
  long long sum_phi = 0;
  long long square_free = 0;
  for (int n = 1; n <= limit; ++n) {
    int rem = n;
    int mobius = 1;
    int custom_expected = 1;
    for (int p = 2; p <= rem; ++p) {
      if (rem % p == 0) {
        int e = 0;
        while (rem % p == 0) {
          rem /= p;
          ++e;
        }

        mobius = e > 1 ? 0 : -mobius;
        custom_expected *= 3 * e + 1;
      }
    }

    long long count = 0;
    long long sum = 0;
    long long coprime = 0;
    for (int d = 1; d <= n; ++d) {
      if (n % d == 0) {
        ++count;
        sum += d;
      }

      coprime += gcd(n, d) == 1;
    }

    // 試し割り・約数列挙・gcdの直接計算で求めた各積性関数の値と比較する。
    assert(mu[n] == mobius && s0[n] == count && s1[n] == sum && phi[n] == coprime &&
           cube[n] == custom_expected);
    sum_phi += coprime;
    square_free += mobius != 0;

    // totientの区間和を、小さい整数ごとに互いに素な数を数えて足した結果と比較する。
    assert(sum_of_totient<long long>(n) == sum_phi);

    // 平方因子を持たない数の個数を、各整数の試し割りの結果から数えた値と比較する。
    assert(count_square_free(n) == square_free);
  }

  mt19937 rng(236);
  for (int n : {1, 2, 7, 32, 100}) {
    vector<long long> a(n + 1);
    vector<long long> b(n + 1);
    vector<long long> dz(n + 1);
    vector<long long> mz(n + 1);
    vector<long long> conv(n + 1);
    for (int i = 1; i <= n; ++i) {
      a[i] = int(rng() % 31) - 15;
      b[i] = int(rng() % 31) - 15;
    }

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (i % j == 0) {
          dz[i] += a[j];
        }

        if (j % i == 0) {
          mz[i] += a[j];
        }

        conv[gcd(i, j)] += a[i] * b[j];
      }
    }

    auto x = a;
    divisor_transform::zeta_transform(x);

    // 約数ゼータ変換を、割り切れる添字の値を全て足した期待値と比較する。
    assert(x == dz);
    divisor_transform::mobius_transform(x);

    // 約数メビウス変換を適用すると、変換前の配列に戻る。
    assert(x == a);
    x = a;
    multiple_transform::zeta_transform(x);

    // 倍数ゼータ変換を、倍数の添字の値を全て足した期待値と比較する。
    assert(x == mz);
    multiple_transform::mobius_transform(x);

    // 倍数メビウス変換を適用すると、変換前の配列に戻る。
    assert(x == a);

    // gcd畳み込みを、添字対を全列挙してgcdの位置へ積を足した結果と比較する。
    assert(gcd_convolution(a, b) == conv);
    map<int, long long> mp;
    for (int i = 1; i <= n; ++i) {
      mp[i] = a[i];
    }

    auto original = mp;
    divisor_transform::zeta_transform(mp);
    for (int i = 1; i <= n; ++i) {
      // mapに対する約数ゼータ変換も、配列で直接計算した値と一致する。
      assert(mp[i] == dz[i]);
    }

    divisor_transform::mobius_transform(mp);

    // mapに対する約数メビウス変換で、元のキーと値が復元される。
    assert(mp == original);
    multiple_transform::zeta_transform(mp);
    for (int i = 1; i <= n; ++i) {
      // mapに対する倍数ゼータ変換も、配列で直接計算した値と一致する。
      assert(mp[i] == mz[i]);
    }

    multiple_transform::mobius_transform(mp);

    // mapに対する倍数メビウス変換で、元のキーと値が復元される。
    assert(mp == original);
  }
}
