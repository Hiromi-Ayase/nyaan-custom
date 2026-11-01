// Verify: multiplicative-function/enumerate-sum-of-multiplicative-function.hpp
// Verify: multiplicative-function/sum-of-multiplicative-function.hpp
// φはgcdの全列挙、約数個数は割り切れ判定で直接計算し、その累積和と比較する。
// Dirichlet積を利用するprefix列挙とMin_25系のrun/sieve、素数個数・素数和のテーブルを検証する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "multiplicative-function/enumerate-sum-of-multiplicative-function.hpp"
#include "multiplicative-function/sum-of-multiplicative-function.hpp"

using M = ModInt<1000000007>;

M divisors_at_prime_power(long long, long long e) {
  return e + 1;
}

int main() {
  const int limit = 1000;
  vector<long long> phi(limit + 1);
  vector<long long> divisors(limit + 1);
  vector<long long> pc(limit + 1);
  vector<long long> ps(limit + 1);
  for (int n = 1; n <= limit; ++n) {
    int ds = 0;
    for (int d = 1; d <= n; ++d) {
      ds += n % d == 0;
      phi[n] += gcd(n, d) == 1;
    }

    phi[n] += phi[n - 1];
    divisors[n] = divisors[n - 1] + ds;
    pc[n] = pc[n - 1] + (ds == 2);
    ps[n] = ps[n - 1] + (ds == 2 ? n : 0);
  }

  for (int n = 1; n <= limit; n += 7) {
    auto sg = [](long long x) { return x; };
    auto sh = [](long long x) { return x * (x + 1) / 2; };
    enumerate_mf_prefix_sum<long long, decltype(sg), decltype(sh)> phi_sum(n, sg, sh);
    mf_prefix_sum<M, divisors_at_prime_power> dsum(n);
    auto pi = dsum.pi_table();
    auto primes = dsum.prime_sum_table();
    auto fp = pi;
    for (auto& x : fp) {
      x *= 2;
    }

    // 約数個数の総和を、全整数の約数を直接数えて累積した表と比較する。
    assert(dsum.run(fp).get() == divisors[n]);
    auto all = dsum.min_25_sieve(fp);
    for (int i = 1; i <= n; ++i) {
      int q = n / i;

      // 商n/iの各位置で、totientの前方和がgcdによる直接計算の表と一致する。
      assert(phi_sum(q) == phi[q]);

      // 素数個数の内部テーブルが、試し割りで判定して累積した個数と一致する。
      assert(pi[dsum.idx(q)].get() == pc[q]);

      // 素数和の内部テーブルが、試し割りで素数だけを足した累積和と一致する。
      assert(primes[dsum.idx(q)].get() == ps[q]);

      // 各商の位置の約数個数の総和を、直接列挙して累積した表と比較する。
      assert(all[dsum.idx(q)].get() == divisors[q]);
    }
  }
}
