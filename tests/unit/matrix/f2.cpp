// Verify: matrix/f2-matrix.hpp
// GF(2)とBoolean積を三重ループ、階数を全ての行のXOR集合の大きさで照合する。
#include <bits/stdc++.h>
using namespace std;
#include "matrix/f2-matrix.hpp"

int main() {
  using Mat = F2_Matrix<8, 8>;
  mt19937 rng(606);
  for (int h = 1; h <= 5; ++h) {
    for (int p = 1; p <= 5; ++p) {
      for (int w = 0; w <= 5; ++w) {
        Mat a(h, p);
        Mat b(p, w);
        for (int i = 0; i < h; ++i) {
          for (int j = 0; j < p; ++j) {
            a[i][j] = rng() % 2;
          }
        }
        for (int i = 0; i < p; ++i) {
          for (int j = 0; j < w; ++j) {
            b[i][j] = rng() % 2;
          }
        }
        auto product = a * b;
        auto boolean = and_or_product(a, b);
        // 長方形の積は、右側の行列に合わせて幅も更新される必要がある。
        assert(product.H == h && product.W == w);
        for (int i = 0; i < h; ++i) {
          for (int j = 0; j < w; ++j) {
            bool parity = false;
            bool exists = false;
            for (int k = 0; k < p; ++k) {
              parity ^= a[i][k] && b[k][j];
              exists = exists || (a[i][k] && b[k][j]);
            }
            // GF(2)の積は経路数の偶奇、Boolean積は経路の存在にそれぞれ対応する。
            assert(product[i][j] == parity);
            assert(boolean[i][j] == exists);
          }
        }
      }
    }
  }

  for (int n = 0; n <= 5; ++n) {
    for (int trial = 0; trial < 200; ++trial) {
      Mat a(n, n);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          a[i][j] = rng() % 2;
        }
      }
      set<unsigned> span;
      for (int mask = 0; mask < (1 << n); ++mask) {
        unsigned x = 0;
        for (int i = 0; i < n; ++i) {
          if (mask >> i & 1) {
            x ^= a[i].to_ulong();
          }
        }
        span.insert(x);
      }
      int rank = 0;
      while ((1U << rank) < span.size()) {
        ++rank;
      }
      auto copy = a;
      // 行のXORの全組合せで作れる異なるベクトルは2^rank個になる。
      assert(copy.sweep() == rank);
      // GF(2)では、正則な行列の行列式は1、特異行列は0である。
      assert(a.determinant() == (rank == n));
      auto [ok, inverse] = a.inverse();
      // 逆行列の存在と、全列挙から求めた階数が一致する。
      assert(ok == (rank == n));
      if (ok) {
        // 左右の逆行列条件を、全ての成分の積和で直接確かめる。
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            bool left = false;
            bool right = false;
            for (int k = 0; k < n; ++k) {
              left ^= a[i][k] && inverse[k][j];
              right ^= inverse[i][k] && a[k][j];
            }
            assert(left == (i == j) && right == (i == j));
          }
        }
      }
    }
  }
}
