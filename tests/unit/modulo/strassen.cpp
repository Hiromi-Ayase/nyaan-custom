// Verify: modulo/strassen.hpp
// 長方形の行列積を整数の三重ループと比較する。SIMD幅・ブロック幅・再帰の切替前後を含む。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modulo/strassen.hpp"

int main() {
  using M = FastMatProd::mint;
  mt19937 rng(611);
  vector<array<int, 3>> shapes{{1, 1, 1},       {2, 3, 5},       {7, 8, 9},
                               {9, 7, 8},       {63, 64, 65},    {65, 63, 64},
                               {127, 128, 129}, {129, 127, 128}, {257, 257, 257}};
  for (auto [h, p, w] : shapes) {
    vector<vector<M>> a(h, vector<M>(p));
    vector<vector<M>> b(p, vector<M>(w));
    for (auto& row : a) {
      for (auto& x : row) {
        x = rng() % M::get_mod();
      }
    }
    for (auto& row : b) {
      for (auto& x : row) {
        x = rng() % M::get_mod();
      }
    }
    vector<vector<M>> expected(h, vector<M>(w));
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        unsigned long long sum = 0;
        for (int k = 0; k < p; ++k) {
          sum = (sum + (unsigned long long)a[i][k].get() * b[k][j].get()) % M::get_mod();
        }
        expected[i][j] = sum;
      }
    }
    // Strassenの分割・加減算を使わない直接の積和と、全成分を比較する。
    assert(FastMatProd::strassen(a, b) == expected);
    // ブロック分割版も同じ結果となり、共有バッファに前の入力の値が残らない。
    assert(FastMatProd::block_dec(a, b) == expected);
  }
}
