// Verify: fps/fps-utility.hpp
// Verify: fps/fps-fraction.hpp
// Verify: fps/middle-product.hpp
// Verify: fps/mod-pow.hpp
// Verify: fps/partial-fraction-decomposition.hpp
// 積・有理式・剰余冪を筆算で検査し、部分分数を通分して元の分子を復元する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/fps-utility.hpp"
#include "fps/fps-fraction.hpp"
#include "fps/middle-product.hpp"
#include "fps/mod-pow.hpp"
#include "fps/partial-fraction-decomposition.hpp"

fps multiply(const fps& a, const fps& b) {
  if (a.empty() || b.empty()) {
    return {};
  }
  fps result(a.size() + b.size() - 1);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size(); ++j) {
      result[i + j] += a[i] * b[j];
    }
  }
  return result;
}

void trim(fps& a) {
  while (!a.empty() && a.back() == 0) {
    a.pop_back();
  }
}

// 高次から1項ずつ消す筆算による剰余。対象ライブラリの除算は使わない。
fps remainder(fps a, const fps& b) {
  trim(a);
  while (a.size() >= b.size()) {
    int shift = a.size() - b.size();
    mint factor = a.back() / b.back();
    for (int i = 0; i < (int)b.size(); ++i) {
      a[i + shift] -= factor * b[i];
    }
    trim(a);
  }
  return a;
}

int main() {
  mt19937 rng(2110);
  for (int n : {1, 2, 3, 7, 32, 64, 65, 129}) {
    fps a(n);
    fps b(n + 3);
    for (auto& c : a) {
      c = rng();
    }
    for (auto& c : b) {
      c = rng();
    }
    fps expected(b.size() - a.size() + 1);
    for (int i = 0; i < (int)expected.size(); ++i) {
      for (int j = 0; j < n; ++j) {
        expected[i] += a[j] * b[i + j];
      }
    }
    // middle productは、ずらした2列の内積を各開始位置で計算する。
    assert(middle_product(a, b) == expected);
    b.back() = 1;
    fps power{1};
    for (int k = 0; k <= 10; ++k) {
      assert(mod_pow(k, a, b) == power);
      power = remainder(multiply(power, a), b);
    }
    vector<fps> factors;
    fps product{1};
    for (int i = 0; i < n; ++i) {
      fps factor{mint(i + 1), 1};
      factors.push_back(factor);
      product = multiply(product, factor);
    }
    // 積の木で得る積が、順に筆算した全係数と一致する。
    assert(Pi(factors) == product);
    vector<mint> roots(n);
    for (int i = 0; i < n; ++i) {
      roots[i] = i;
    }
    auto coefficients = PartialFractionDecomposition(a, roots);
    fps reconstructed(n);
    for (int i = 0; i < n; ++i) {
      fps term{coefficients[i]};
      for (int j = 0; j < n; ++j) {
        if (i != j) {
          term = multiply(term, fps{-roots[j], 1});
        }
      }
      for (int j = 0; j < n; ++j) {
        reconstructed[j] += term[j];
      }
    }
    // すべての分数を通分すると元の分子に戻る。根0も含める。
    assert(reconstructed == a);
  }
  assert(Pi(vector<fps>{}) == fps{1});
  for (int trial = 0; trial < 30; ++trial) {
    vector<pair<mint, int>> poles{{2, 1}, {3, 3}, {7, 2}};
    fps numerator(6);
    for (auto& c : numerator) {
      c = rng();
    }
    auto parts = PartialFractionDecomposition(numerator, poles);
    fps reconstructed(6);
    for (auto [pole, coefficients] : parts) {
      for (int k = 0; k < (int)coefficients.size(); ++k) {
        fps term{coefficients[k]};
        for (auto [other, multiplicity] : poles) {
          int count = multiplicity - (other == pole ? k + 1 : 0);
          for (int i = 0; i < count; ++i) {
            term = multiply(term, fps{other, 1});
          }
        }
        for (int i = 0; i < (int)term.size(); ++i) {
          reconstructed[i] += term[i];
        }
      }
    }
    // 重根を持つ旧APIも、(x+pole)の各冪を消して通分する。
    assert(reconstructed == numerator);
  }
  using fraction = fps_fraction<fps>;
  fraction a(fps{2, 3}, fps{1, 4});
  fraction b(fps{5, 6}, fps{7, 8});
  for (int x = 0; x < 20; ++x) {
    auto value = [&](fraction f) { return f.p.eval(x) / f.q.eval(x); };
    // 有理式の四則と逆数を、分母が0でない点での体の演算に照合する。
    assert(value(a + b) == value(a) + value(b));
    assert(value(a - b) == value(a) - value(b));
    assert(value(a * b) == value(a) * value(b));
    assert(value(a / b) == value(a) / value(b));
    assert(value(a.inverse()) == value(a).inverse());
    assert(value(a + mint(3)) == value(a) + 3);
    assert(value(a / mint(3)) == value(a) / 3);
  }
}
