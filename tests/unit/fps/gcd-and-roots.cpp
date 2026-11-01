// Verify: fps/polynomial-gcd.hpp
// Verify: fps/root-finding.hpp
// 多項式GCDを筆算のEuclid法と比較し、既知の重根と非可約因子から全根を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/polynomial-gcd.hpp"
#include "fps/root-finding.hpp"

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
  mt19937 rng(2111);
  for (int n : {0, 1, 2, 3, 17, 64, 65, 129, 257}) {
    fps a(n);
    fps b(n + 3);
    for (auto& c : a) {
      c = rng();
    }
    for (auto& c : b) {
      c = rng();
    }
    b.back() = 3;
    fps common{2, 5, 1};
    a = multiply(a, common);
    b = multiply(b, common);
    fps x = a;
    fps y = b;
    trim(x);
    trim(y);
    while (!y.empty()) {
      fps next = remainder(x, y);
      x = y;
      y = next;
    }
    if (!x.empty()) {
      mint leading = x.back();
      for (auto& c : x) {
        c /= leading;
      }
    }
    // 共通因子・零多項式を含むGCDをモニックに正規化して比較する。
    assert(PolyGCD(a, b) == x);
    auto inverse = PolyInv(a, b);
    assert(bool(inverse.first) == (x.size() == 1));
    fps modulus(n + 3);
    for (auto& c : modulus) {
      c = rng();
    }
    modulus.back() = 1;
    auto candidate = PolyInv(fps{2, 1}, modulus);
    fps expected = remainder(modulus, fps{2, 1});
    assert(bool(candidate.first) == !expected.empty());
    if (candidate.first) {
      // 逆元の積を筆算して法多項式で割った余りは1になる。
      assert(remainder(multiply(candidate.second, fps{2, 1}), modulus) == fps{1});
    }
  }
  mint nonresidue = 2;
  while (nonresidue.pow((mint::get_mod() - 1) / 2) == 1) {
    nonresidue += 1;
  }
  for (int n : {0, 1, 2, 7, 20}) {
    fps polynomial{-nonresidue, 0, 1};
    vector<int> expected;
    for (int i = 0; i < n; ++i) {
      int root = i * i + 3;
      expected.push_back(root);
      for (int count = 0; count <= i % 3; ++count) {
        polynomial = multiply(polynomial, fps{-mint(root), 1});
      }
    }
    auto actual = root_finding(polynomial);
    vector<int> values;
    for (auto value : actual) {
      values.push_back(value.get());
    }
    sort(values.begin(), values.end());
    // 重複根は1回ずつ返り、平方非剰余から作った2次因子から根は増えない。
    assert(values == expected);
  }
}
