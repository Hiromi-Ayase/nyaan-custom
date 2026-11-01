// Verify: ntt/cooley-tukey-ntt.hpp
// Verify: ntt/rader-ntt.hpp
// 定義どおりのO(N^2)離散フーリエ変換と比較する。2冪・混合基数・大きな素数長を通す。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "ntt/cooley-tukey-ntt.hpp"
#include "ntt/rader-ntt.hpp"

// 2801-1 = 2^4 * 5^2 * 7。素数長は別の法でRader法を直接確認する。
template <int Mod>
void check(const vector<int>& lengths, bool direct_rader) {
  using M = ModInt<Mod>;
  mt19937 rng(9044);
  int primitive = 2;
  for (;; ++primitive) {
    vector<bool> seen(Mod);
    int x = 1;
    for (int k = 0; k < Mod - 1; ++k) {
      seen[x] = true;
      x = 1LL * x * primitive % Mod;
    }
    if (count(seen.begin(), seen.end(), true) == Mod - 1) {
      break;
    }
  }
  ArbitraryLengthNTT<M> ntt(Mod - 1);
  for (int n : lengths) {
    vector<M> a(n);
    for (auto& x : a) {
      x = rng() % Mod;
    }
    // ライブラリの原始根に依存せず、全剰余を生成できる底を探索して期待値を作る。
    M step = M(primitive).pow((Mod - 1) / n);
    vector<M> expected(n);
    for (int i = 0; i < n; ++i) {
      M point = step.pow(i);
      M power = 1;
      for (int j = 0; j < n; ++j) {
        expected[i] += a[j] * power;
        power *= point;
      }
    }
    auto got = a;
    ntt.ntt(got);
    // 周波数の順番も含め、定義式で直接計算したDFTと一致する。
    assert(got == expected);
    ntt.intt(got);
    // 逆変換の正規化によって、元の係数列を正確に復元する。
    assert(got == a);

    if (direct_rader && n > 2) {
      vector<M> roots(n);
      roots[0] = 1;
      for (int i = 1; i < n; ++i) {
        roots[i] = roots[i - 1] * step;
      }
      RaderNTT<M> rader(n, n, roots);
      got = a;
      rader.ntt(got);
      // Raderの素数長変換を直接呼び出しても、同じDFT定義に一致する。
      assert(got == expected);
    }
  }
}

int main() {
  check<2801>({1, 2, 5, 7, 16, 25, 70, 100, 112, 175, 400}, false);
  check<269>({67, 134, 268}, false);
  check<269>({67}, true);
}
