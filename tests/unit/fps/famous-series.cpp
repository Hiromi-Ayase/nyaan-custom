// Verify: fps/fps-famous-series.hpp
// Verify: fps/fualhuber.hpp
// Verify: fps/lagrange-interpolation-point.hpp
// Verify: fps/sum-of-exponential-times-poly.hpp
// 組合せ数列を初等DPで求め、べき和と指数付き和を項ごとの加算と比較する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/fps-famous-series.hpp"
#include "fps/fualhuber.hpp"
#include "fps/lagrange-interpolation-point.hpp"
#include "fps/sum-of-exponential-times-poly.hpp"

mint evaluate(const fps& f, mint x) {
  mint result = 0;
  for (int i = int(f.size()) - 1; i >= 0; --i) {
    result = result * x + f[i];
  }
  return result;
}

int main() {
  Binomial<mint> binomial;
  const int limit = 130;
  vector<fps> first(limit + 1, fps(limit + 1));
  vector<fps> second = first;
  first[0][0] = 1;
  second[0][0] = 1;
  for (int n = 1; n <= limit; ++n) {
    for (int k = 1; k <= n; ++k) {
      first[n][k] = first[n - 1][k - 1] + first[n - 1][k] * (n - 1);
      second[n][k] = second[n - 1][k - 1] + second[n - 1][k] * k;
    }
  }
  for (int n = 0; n <= limit; ++n) {
    // 第1種/第2種の行・列が、挿入する要素を考えた基本漸化式に一致する。
    assert(Stirling1st(n, binomial) == first[n].pre(n + 1));
    assert(Stirling2nd(n, binomial) == second[n].pre(n + 1));
    auto a = Stirling1stRow(n, limit, binomial);
    auto b = Stirling2ndRow(n, limit, binomial);
    for (int i = 0; i <= limit; ++i) {
      assert(a[i] == first[i][n] && b[i] == second[i][n]);
    }
  }
  fps partitions(limit + 1);
  partitions[0] = 1;
  for (int part = 1; part <= limit; ++part) {
    for (int total = part; total <= limit; ++total) {
      partitions[total] += partitions[total - part];
    }
  }
  // 整数分割は、使用可能な部品サイズを増やすナップサックDPと比較する。
  assert(Partition(limit, binomial) == partitions);
  for (int n = 1; n <= 8; ++n) {
    vector<int> permutation(n);
    iota(permutation.begin(), permutation.end(), 0);
    int derangements = 0;
    do {
      bool valid = true;
      for (int i = 0; i < n; ++i) {
        valid = valid && permutation[i] != i;
      }
      derangements += valid;
    } while (next_permutation(permutation.begin(), permutation.end()));
    assert(Montmort<mint>(n).back() == derangements);
  }
  auto bernoulli = BernoulliEGF(limit, binomial);
  mint factorial = 1;
  fps denominator(limit + 1);
  for (int i = 0; i <= limit; ++i) {
    factorial *= i + 1;
    denominator[i] = factorial.inverse();
  }
  for (int k = 0; k <= limit; ++k) {
    mint coefficient = 0;
    for (int i = 0; i <= k; ++i) {
      coefficient += bernoulli[i] * denominator[k - i];
    }
    // Bernoulli EGFは(exp(x)-1)/xの逆数という定義を満たす。
    assert(coefficient == (k == 0 ? 1 : 0));
  }
  mt19937 rng(2109);
  for (int degree : {0, 1, 2, 7, 16, 65}) {
    fps f(degree + 1);
    for (auto& c : f) {
      c = rng();
    }
    auto prefix_polynomial = fualhuber(f, binomial);
    mint prefix = 0;
    vector<mint> samples(degree + 1);
    for (int i = 0; i <= degree; ++i) {
      samples[i] = evaluate(f, i);
    }
    for (int i = 0; i <= 150; ++i) {
      prefix += evaluate(f, i);
      // 0からiまでの和が、返された多項式をiで評価した値になる。
      assert(evaluate(prefix_polynomial, i) == prefix);
    }
    for (mint ratio : {mint(0), mint(1), mint(2), mint(-1)}) {
      mint total = 0;
      mint power = 1;
      mint powers_total = 0;
      for (int n = 0; n <= 90; ++n) {
        assert(sum_of_exp(samples, ratio, n, binomial) == total);
        assert(sum_of_exp2(degree, ratio, n, binomial) == powers_total);
        total += power * evaluate(f, n);
        powers_total += power * mint(n).pow(degree);
        power *= ratio;
      }
    }
    auto powers = exp_enamurate<mint>(degree, 150);
    for (int i = 0; i <= 150; ++i) {
      assert(powers[i] == mint(i).pow(degree));
    }
  }
  for (mint ratio : {mint(0), mint(2), mint(7)}) {
    // 定数列と一次列の無限和は、等比級数の有理式として検査する。
    assert(sum_of_exp_limit(vector<mint>{1}, ratio, binomial) == mint(1) / (mint(1) - ratio));
    assert(sum_of_exp_limit2(1, ratio, binomial) ==
           ratio / ((mint(1) - ratio) * (mint(1) - ratio)));
  }
}
