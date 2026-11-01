// Verify: ntt/chirp-z.hpp
// Verify: ntt/convolution-large.hpp
// Verify: ntt/relaxed-convolution.hpp
// Verify: ntt/multivariate-multiplication.hpp
// Verify: ntt/multiplicative-convolution-mod-p.hpp
// 多項式の直接評価と添字対の全列挙を参照に、特殊な添字規則やオンライン計算を照合する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
#include "ntt/chirp-z.hpp"
#include "ntt/convolution-large.hpp"
#include "ntt/relaxed-convolution.hpp"
#include "ntt/multivariate-multiplication.hpp"
#include "ntt/multiplicative-convolution-mod-p.hpp"

using M = LazyMontgomeryModInt<998244353>;
using F = FormalPowerSeries<M>;

int main() {
  mt19937 rng(9045);
  for (int size : {0, 1, 2, 17, 64, 129}) {
    F f(size);
    for (auto& x : f) {
      x = rng() % M::get_mod();
    }
    for (int n : {0, 1, 31, 65, 130}) {
      for (int w : {0, 1, 2, 17}) {
        for (int a : {0, 1, 7}) {
          F expected(n);
          M point = a;
          for (int i = 0; i < n; ++i) {
            M power = 1;
            for (M c : f) {
              expected[i] += c * power;
              power *= point;
            }
            point *= w;
          }
          // 等比数列上の各点へ直接代入した値と比較する。W=0や空多項式も含む。
          assert(ChirpZ(f, M(w), n, M(a)) == expected);
        }
      }
    }
  }

  // 法17ではNTT長の上限が16なので、小さな入力でも分割畳み込みの経路を通せる。
  using Small = LazyMontgomeryModInt<17>;
  using SmallF = FormalPowerSeries<Small>;
  for (int n : {0, 1, 7, 8, 9, 16, 17, 33, 65}) {
    for (int m : {0, 1, 8, 17, 41}) {
      SmallF a(n);
      SmallF b(m);
      for (auto& x : a) {
        x = rng() % 17;
      }
      for (auto& x : b) {
        x = rng() % 17;
      }
      SmallF expected(n && m ? n + m - 1 : 0);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          expected[i + j] += a[i] * b[j];
        }
      }
      // NTT長を超える積も、分割の継ぎ目を含めて通常の多項式積になる。
      assert(convolution_large(a, b) == expected);
    }
  }

  for (int n : {0, 1, 2, 31, 32, 33, 127, 256, 513}) {
    RelaxedConvolution<F> online(n);
    F a(n + 1);
    F b(n + 1);
    for (int k = 0; k <= n; ++k) {
      a[k] = rng() % M::get_mod();
      b[k] = rng() % M::get_mod();
      M expected = 0;
      for (int i = 0; i <= k; ++i) {
        expected += a[i] * b[k - i];
      }
      // k番目の入力を与えた直後に、既知の入力だけで決まるk次係数を取得できる。
      assert(online.get(a[k], b[k]) == expected);
    }
  }

  for (vector<int> base : vector<vector<int>>{{}, {1}, {7}, {2, 3}, {3, 4, 2}, {2, 2, 2, 2}}) {
    int n = accumulate(base.begin(), base.end(), 1, multiplies<int>());
    F a(n);
    F b(n);
    for (auto& x : a) {
      x = rng() % 1000;
    }
    for (auto& x : b) {
      x = rng() % 1000;
    }
    F expected(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int x = i;
        int y = j;
        bool valid = true;
        for (int radix : base) {
          if (x % radix + y % radix >= radix) {
            valid = false;
          }
          x /= radix;
          y /= radix;
        }
        if (valid) {
          expected[i + j] += a[i] * b[j];
        }
      }
    }
    // どの変数の次数も上限を超えない添字対だけを足した多変数積と一致する。
    assert(multivariate_multiplication(a, b, base) == expected);
  }

  for (int p : {2, 3, 5, 17, 101, 257}) {
    F a(p);
    F b(p);
    for (auto& x : a) {
      x = rng() % 1000;
    }
    for (auto& x : b) {
      x = rng() % 1000;
    }
    F expected(p);
    for (int i = 0; i < p; ++i) {
      for (int j = 0; j < p; ++j) {
        expected[i * j % p] += a[i] * b[j];
      }
    }
    // 添字の積が同じ剰余になる全組を足す。特別扱いされる添字0の寄与も照合する。
    assert(multiplicative_convolution_mod_p(a, b, p) == expected);
  }
}
