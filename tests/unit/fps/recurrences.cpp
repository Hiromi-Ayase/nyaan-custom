// Verify: fps/berlekamp-massey.hpp
// Verify: fps/kitamasa.hpp
// Verify: fps/nth-term.hpp
// Verify: fps/find-p-recursive.hpp
// 線形漸化式と多項式係数の漸化式を逐次計算し、学習に使わない後続項まで検証する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/berlekamp-massey.hpp"
#include "fps/kitamasa.hpp"
#include "fps/nth-term.hpp"
#include "fps/find-p-recursive.hpp"

int main() {
  mt19937 rng(2108);
  for (int order : {1, 2, 3, 16, 64, 65}) {
    fps denominator(order + 1);
    denominator[0] = 1;
    for (int i = 1; i <= order; ++i) {
      denominator[i] = rng();
    }
    fps sequence(700);
    for (int i = 0; i < order; ++i) {
      sequence[i] = rng();
    }
    for (int i = order; i < (int)sequence.size(); ++i) {
      for (int j = 1; j <= order; ++j) {
        sequence[i] -= denominator[j] * sequence[i - j];
      }
    }
    vector<mint> prefix(sequence.begin(), sequence.begin() + 2 * order + 5);
    auto found = BerlekampMassey(prefix);
    for (int i = prefix.size(); i < (int)sequence.size(); ++i) {
      mint residual = 0;
      for (int j = 0; j < (int)found.size(); ++j) {
        residual += found[j] * sequence[i - j];
      }
      // 発見した関係式は、入力に含まれない後続項でも成立する。
      assert(residual == 0);
    }
    for (int k : {0, 1, order, 2 * order, 300, 699}) {
      assert(kitamasa(k, denominator, sequence.pre(order)) == sequence[k]);
      assert(nth_term(k, prefix) == sequence[k]);
    }
    fps numerator(order + 3);
    for (auto& c : numerator) {
      c = rng();
    }
    fps quotient(700);
    for (int i = 0; i < (int)quotient.size(); ++i) {
      quotient[i] = i < (int)numerator.size() ? numerator[i] : mint(0);
      for (int j = 1; j <= order && j <= i; ++j) {
        quotient[i] -= denominator[j] * quotient[i - j];
      }
    }
    // 分子の次数が分母以上でも、形式的な除算の係数と一致する。
    for (int k : {0, 3, 80, 699}) {
      assert(LinearRecurrence(k, denominator, numerator) == quotient[k]);
    }
  }
  // 非常に遠い項は、等比数列の閉じた式で確認する。
  long long k = 1000000000000000000LL;
  assert(kitamasa(k, fps{1, -7}, fps{3}) == mint(3) * mint(7).pow(k));
  assert(nth_term(k, vector<mint>(10, 0)) == 0);
  for (int kind = 0; kind < 3; ++kind) {
    vector<mint> sequence(301, 1);
    for (int i = 1; i <= 300; ++i) {
      if (kind == 0) {
        sequence[i] = sequence[i - 1] * i;
      }
      if (kind == 1) {
        sequence[i] = sequence[i - 1] * (4 * i - 2) / (i + 1);
      }
      if (kind == 2) {
        sequence[i] = sequence[i - 1] * (i * i + 1);
      }
    }
    vector<mint> prefix(sequence.begin(), sequence.begin() + 12);
    int degree = kind == 2 ? 2 : 1;
    auto relation = find_p_recursive(prefix, degree);
    int order = relation.size() - 1;
    // 係数多項式も後続項で検査し、単に先頭項を暗記していないことを確かめる。
    assert(order >= 1);
    for (int i = 12; i + order <= 300; ++i) {
      mint residual = 0;
      for (int j = 0; j <= order; ++j) {
        residual += relation[j].eval(i) * sequence[i + order - j];
      }
      assert(residual == 0);
    }
    for (int index : {0, 11, 12, 37, 300}) {
      assert(kth_term_of_p_recursive(prefix, index, degree) == sequence[index]);
    }
    assert(kth_term_of_p_recursive_enumerate(prefix, 301, degree) == sequence);
  }
}
