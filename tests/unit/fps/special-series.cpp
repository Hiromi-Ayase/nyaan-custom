// Verify: fps/fps-sqrt.hpp
// Verify: fps/sparse-fps.hpp
// Verify: fps/inversion-formula.hpp
// Verify: fps/fps-circular.hpp
// 平方根・疎な級数・三角関数を、筆算および微分方程式の係数比較で検査する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
#include "fps/fps-sqrt.hpp"
#include "fps/sparse-fps.hpp"
#include "fps/inversion-formula.hpp"
#include "fps/fps-circular.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;

// 係数を全組み合わせで掛ける筆算。検査対象の畳み込みは使わない。
fps multiply(const fps& a, const fps& b, int n) {
  fps c(n);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size() && i + j < n; ++j) {
      c[i + j] += a[i] * b[j];
    }
  }
  return c;
}

fps exponential(const fps& a, int n) {
  fps result(n);
  if (n > 0) {
    result[0] = 1;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= i && j < (int)a.size(); ++j) {
      result[i] += mint(j) * a[j] * result[i - j];
    }
    result[i] /= i;
  }
  return result;
}

int main() {
  mt19937 rng(2102);
  for (int n : {1, 2, 3, 16, 63, 64, 65, 129, 257}) {
    fps a(n);
    for (int i = 1; i < n; ++i) {
      if (rng() % 5 == 0) {
        a[i] = rng();
      }
    }
    a[0] = 1;
    fps one(n);
    one[0] = 1;
    // 高速版と独立に、逆数・平方根の定義を筆算で確認する。
    assert(multiply(a, n2_inv(a), n) == one);
    assert(multiply(a, sparse_inv(a), n) == one);
    assert(multiply(n2_sqrt(a), n2_sqrt(a), n) == a);
    assert(exponential(n2_log(a), n) == a);
    assert(exponential(sparse_log(a), n) == a);
    fps numerator(n + 3, 7);
    auto quotient = sparse_div(numerator, a, n + 3);
    assert(multiply(quotient, a, n + 3) == numerator);
    fps power = one;
    for (int k = 0; k <= 5; ++k) {
      // 疎な冪の各係数を繰り返し筆算で求める。
      assert(sparse_pow(a, k) == power);
      power = multiply(power, a, n);
    }
    a[0] = 0;
    assert(n2_exp(a) == exponential(a, n));
    assert(sparse_exp(a) == exponential(a, n));
    fps imaginary(n);
    for (int i = 1; i < n; ++i) {
      imaginary[i] = rng() % 10;
    }
    fps real(n);
    fps imag(n);
    real[0] = 1;
    for (int k = 1; k < n; ++k) {
      for (int j = 1; j <= k; ++j) {
        real[k] -= mint(j) * (imaginary[j] * real[k - j] + a[j] * imag[k - j]);
        imag[k] += mint(j) * (a[j] * real[k - j] - imaginary[j] * imag[k - j]);
      }
      real[k] /= k;
      imag[k] /= k;
    }
    // exp(-imaginary+i*a) の実部・虚部を、複素数の微分公式から求める。
    auto actual = circular(a, imaginary);
    assert(actual.first == real && actual.second == imag);
    for (int shift : {0, 1, 3}) {
      fps source(n);
      for (int i = shift; i < n; ++i) {
        source[i] = rng();
      }
      fps square = multiply(source, source, n);
      fps result = sqrt(square);
      // 平方根の符号は問わず、再度二乗すると元の級数になる。
      assert(result.size() == square.size());
      assert(multiply(result, result, n) == square);
    }
  }
  // 最初の非零項が奇数次数なら平方根は存在しない。
  assert(sqrt(fps{0, 1, 0}).empty());
  mint nonresidue = 2;
  while (nonresidue.pow((mint::get_mod() - 1) / 2) == 1) {
    nonresidue += 1;
  }
  assert(sqrt(fps{nonresidue}).empty());
  assert(sqrt(fps{}, 5) == fps(5));
  assert(sparse_pow(fps{0, 0, 2}, 1000000000000000000LL, 8) == fps(8));
}
