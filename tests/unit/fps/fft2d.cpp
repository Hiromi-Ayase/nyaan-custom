// Verify: fps/fft2d.hpp
// 二変数の積を4重ループで求め、ナイーブ・部分FFT・全面FFTの各経路を比較する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/fft2d.hpp"

int main() {
  mt19937 rng(2114);
  for (auto shape : vector<array<int, 4>>{{1, 1, 1, 1},
                                          {2, 3, 3, 2},
                                          {7, 8, 9, 10},
                                          {3, 65, 17, 33},
                                          {41, 45, 42, 47},
                                          {43, 50, 51, 48}}) {
    int h = shape[0];
    int w = shape[1];
    int p = shape[2];
    int q = shape[3];
    vector<fps> a(h, fps(w));
    vector<fps> b(p, fps(q));
    for (auto& row : a) {
      for (auto& c : row) {
        c = rng();
      }
    }
    for (auto& row : b) {
      for (auto& c : row) {
        c = rng();
      }
    }
    vector<fps> expected(h + p - 1, fps(w + q - 1));
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        for (int k = 0; k < p; ++k) {
          for (int l = 0; l < q; ++l) {
            expected[i + k][j + l] += a[i][j] * b[k][l];
          }
        }
      }
    }
    // 軸の入れ替えや長さ調整の分岐を含め、全係数を照合する。
    assert(multiply2d(a, b) == expected);
    assert(multiply2d_partially_naive(a, b) == expected);
    assert(multiply2d_naive(a, b) == expected);
    auto transposed = transpose(a);
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        assert(transposed[j][i] == a[i][j]);
      }
    }
  }
  for (int h : {1, 2, 4, 16}) {
    for (int w : {1, 2, 8, 32}) {
      vector<fps> a(h, fps(w));
      for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
          if (i % 2 == 0) {
            a[i][j] = rng();
          }
        }
      }
      auto transformed = a;
      fft2d(transformed);
      ifft2d(transformed);
      // 全零の行を持つ場合も、正変換と逆変換で元に戻る。
      assert(transformed == a);
    }
  }
  assert(multiply2d(vector<fps>{}, vector<fps>{fps{1}}).empty());
}
