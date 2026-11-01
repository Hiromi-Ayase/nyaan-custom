// Verify: math/affine-transformation.hpp
// Verify: math/gray-code.hpp
// アフィン変換の合成順を直接代入で、Gray符号を全状態の被覆と隣接ビット差で検証する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/affine-transformation.hpp"
#include "math/gray-code.hpp"

int main() {
  for (long long a = -3; a <= 3; ++a) {
    for (long long b = -3; b <= 3; ++b) {
      Affine<long long> f(a, b);
      for (long long c = -3; c <= 3; ++c) {
        for (long long d = -3; d <= 3; ++d) {
          Affine<long long> g(c, d);
          for (int x = -5; x <= 5; ++x) {
            // operator*は左を先に適用するため、結果はg(f(x))になる。
            assert((f * g)(x) == c * (a * x + b) + d);
            // 関数呼出し形式での合成は、通常どおりf(g(x))になる。
            assert(f(g)(x) == a * (c * x + d) + b);
            // 既定の変換は恒等写像であり、符号付きの入力も変えない。
            assert(Affine<long long>()(x) == x);
          }
        }
      }
    }
  }
  for (int bits = 0; bits <= 16; ++bits) {
    auto codes = gray_code(bits);
    auto sorted = codes;
    sort(sorted.begin(), sorted.end());
    for (int i = 0; i < (1 << bits); ++i) {
      // 全ビット列をちょうど1回ずつ含み、重複や欠落がない。
      assert(sorted[i] == i);
      if (bits > 0) {
        // 最後から最初への遷移も含め、隣り合う符号はちょうど1bitだけ異なる。
        assert(__builtin_popcount((unsigned)(codes[i] ^ codes[(i + 1) % codes.size()])) == 1);
      }
    }
  }
}
