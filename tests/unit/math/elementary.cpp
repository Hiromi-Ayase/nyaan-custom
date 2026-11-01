// Verify: math/elementary-function.hpp
// Verify: math/constexpr-primitive-root.hpp
// Verify: math/primitive-root-ll.hpp
// Verify: math/inv-mod.hpp
// Verify: math/garner.hpp
// 約数・素因数・互いに素な個数を直接走査し、逆元・合同式・原始根も小さい法で全探索する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/elementary-function.hpp"
#include "math/constexpr-primitive-root.hpp"
#include "math/primitive-root-ll.hpp"
#include "math/inv-mod.hpp"
#include "math/garner.hpp"

int main() {
  vector<long long> primes;
  for (int n = 2; n <= 2000; ++n) {
    bool prime = true;
    for (int d = 2; d < n; ++d) {
      if (n % d == 0) {
        prime = false;
        break;
      }
    }
    if (prime) {
      primes.push_back(n);
    }
  }
  auto totient = EulersTotientFunction(2000);
  for (int n = 1; n <= 2000; ++n) {
    vector<long long> divisors;
    int coprime = 0;
    for (int d = 1; d <= n; ++d) {
      if (n % d == 0) {
        divisors.push_back(d);
      }
      coprime += gcd(n, d) == 1;
    }
    auto got = Divisor(n);
    sort(got.begin(), got.end());
    // 約数の順序は規定しないためソートし、割り切れる整数を全て集めた集合と比較する。
    assert(got == divisors);
    // 一括計算したtotientと単独版の両方を、gcdで数えた個数と比較する。
    assert(totient[n] == coprime && phi(n) == coprime);
    vector<pair<long long, int>> factors;
    int remaining = n;
    for (int p = 2; p <= remaining; ++p) {
      int exponent = 0;
      while (remaining % p == 0) {
        remaining /= p;
        ++exponent;
      }
      if (exponent) {
        factors.emplace_back(p, exponent);
      }
    }
    // 素数表なし・ありの両版を、2から順に繰り返し割った因数と指数に照合する。
    assert(PrimeFactors(n) == factors);
    assert(PrimeFactors(n, primes) == factors);
    int square = -1;
    for (int r = 0; r * r <= n; ++r) {
      if (r * r == n) {
        square = r;
      }
    }
    // 完全平方数だけが非負の平方根を返し、それ以外は-1になる。
    assert(SqrtInt(n) == square);
    // 桁数を十進文字列の長さと比較する。
    assert(isDigit(n) == (int)to_string(n).size());
  }
  // 0の桁数には既定値1と、明示した任意の値を使える。
  assert(isDigit(0) == 1 && isDigit(0, 7) == 7 && SqrtInt(0) == 0);

  for (long long a = 0; a <= 80; ++a) {
    for (long long b = 0; b <= 80; ++b) {
      auto [x, y] = extgcd(a, b);
      // 拡張Euclidの係数は、0を含む非負入力でもBezoutの等式を満たす。
      assert(a * x + b * y == gcd(a, b));
    }
  }
  for (long long mod = 1; mod <= 100; ++mod) {
    for (long long a = -mod; a <= 2 * mod; ++a) {
      if (gcd(a, mod) != 1) {
        continue;
      }
      long long expected = 0;
      while (((a % mod + mod) % mod) * expected % mod != 1 % mod) {
        ++expected;
      }
      // 各剰余を試して見つけた逆元と比較する。法1では0を返す。
      assert(inv_mod(a, mod) == expected);
    }
    for (long long a = 0; a <= 100; ++a) {
      long long expected = 1 % mod;
      for (int e = 0; e <= 20; ++e) {
        // 冪剰余を逐次乗算と比較し、指数0と法1も確認する。
        assert(modpow(a, e, mod) == expected);
        expected = expected * a % mod;
      }
    }
  }
  for (long long p : primes) {
    for (long long g :
         {PrimitiveRoot(p), (long long)constexpr_primitive_root(p), primitive_root_ll(p)}) {
      set<long long> generated;
      long long x = 1;
      for (int i = 0; i < p - 1; ++i) {
        generated.insert(x);
        x = x * g % p;
      }
      // 返された根の冪が、非零剰余をちょうど1回ずつ生成する。
      assert((int)generated.size() == p - 1 && x == 1);
      // 原始根の判定APIでも、生成を直接確認した根を受理する。
      assert(isPrimitiveRoot(g, p));
    }
  }
  for (unsigned long long m = 1; m <= 20; ++m) {
    for (unsigned long long n = 1; n <= 20; ++n) {
      for (unsigned long long a = 0; a < m; ++a) {
        for (unsigned long long b = 0; b < n; ++b) {
          auto [r, period] = garner(vector{a, b}, vector{m, n});
          unsigned long long length = lcm(m, n);
          unsigned long long expected = length;
          for (unsigned long long x = 0; x < length; ++x) {
            if (x % m == a && x % n == b) {
              expected = x;
              break;
            }
          }
          // 非互いに素な法も含め、1周期を全探索した最小解と周期に一致する。
          assert(expected == length ? period == 0 : r == expected && period == length);
        }
      }
    }
  }
}
