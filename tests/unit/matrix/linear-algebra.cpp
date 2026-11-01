// Verify: matrix/gauss-elimination.hpp
// Verify: matrix/linear-equation.hpp
// Verify: matrix/inverse-matrix.hpp
// GF(3)の全ベクトルを列挙して像・核・解集合を求める。長方形、零行列、解なし、自由変数を含む。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "matrix/gauss-elimination.hpp"
#include "matrix/linear-equation.hpp"
#include "matrix/inverse-matrix.hpp"

using M = ModInt<3>;

int main() {
  mt19937 rng(601);
  vector<vector<M>> empty;
  auto empty_result = GaussElimination(empty);
  // 空行列の階数は0、空積としての行列式は1になる。
  assert(empty_result.first == 0 && empty_result.second == M(1));

  for (int h = 1; h <= 4; ++h) {
    for (int w = 0; w <= 4; ++w) {
      for (int trial = 0; trial < 60; ++trial) {
        vector<vector<M>> a(h, vector<M>(w));
        vector<M> b(h);
        for (int i = 0; i < h; ++i) {
          b[i] = rng() % 3;
          for (int j = 0; j < w; ++j) {
            a[i][j] = trial == 0 ? 0 : rng() % 3;
          }
        }
        int count = 1;
        for (int j = 0; j < w; ++j) {
          count *= 3;
        }
        set<vector<int>> image;
        set<vector<int>> expected;
        for (int mask = 0; mask < count; ++mask) {
          int digits = mask;
          vector<int> x(w);
          for (int j = 0; j < w; ++j) {
            x[j] = digits % 3;
            digits /= 3;
          }
          vector<int> y(h);
          bool solution = true;
          for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
              y[i] = (y[i] + a[i][j].get() * x[j]) % 3;
            }
            if (y[i] != b[i].get()) {
              solution = false;
            }
          }
          image.insert(y);
          if (solution) {
            expected.insert(x);
          }
        }
        int rank = 0;
        for (int size = image.size(); size > 1; size /= 3) {
          ++rank;
        }
        auto echelon = a;
        auto [actual_rank, det] = GaussElimination(echelon);
        // 線形写像の像の要素数は3^rankになるので、消去法と異なる方法で階数を照合できる。
        assert(actual_rank == rank);

        auto basis = LinearEquation(a, b);
        set<vector<int>> got;
        if (!basis.empty()) {
          int combinations = 1;
          for (int i = 1; i < (int)basis.size(); ++i) {
            combinations *= 3;
          }
          for (int mask = 0; mask < combinations; ++mask) {
            auto x = basis[0];
            int digits = mask;
            for (int i = 1; i < (int)basis.size(); ++i) {
              for (int j = 0; j < w; ++j) {
                x[j] += basis[i][j] * (digits % 3);
              }
              digits /= 3;
            }
            vector<int> row;
            for (M value : x) {
              row.push_back(value.get());
            }
            got.insert(row);
          }
          // 基底が冗長なら生成した解に重複が生じるため、全組合せ数と異なる解の数を比べる。
          assert((int)got.size() == combinations);
        }
        // 特殊解と基底から生成した解集合が、全ベクトル代入で得た集合と完全に一致する。
        assert(got == expected);

        if (h == w) {
          vector<int> permutation(h);
          iota(permutation.begin(), permutation.end(), 0);
          M expected_det = 0;
          do {
            M term = 1;
            for (int i = 0; i < h; ++i) {
              term *= a[i][permutation[i]];
              for (int j = 0; j < i; ++j) {
                if (permutation[j] > permutation[i]) {
                  term = -term;
                }
              }
            }
            expected_det += term;
          } while (next_permutation(permutation.begin(), permutation.end()));
          // 行交換の符号や特異行列を含め、Leibnizの定義式で求めた行列式と一致する。
          assert(det == expected_det);

          auto inverse = inverse_matrix(a);
          // 全列挙で求めた階数が最大のときだけ、逆行列が存在する。
          assert(inverse.empty() == (rank != h));
          if (!inverse.empty()) {
            for (int i = 0; i < h; ++i) {
              for (int j = 0; j < h; ++j) {
                M left = 0;
                M right = 0;
                for (int k = 0; k < h; ++k) {
                  left += a[i][k] * inverse[k][j];
                  right += inverse[i][k] * a[k][j];
                }
                // 左右どちらから掛けても単位行列になり、転置や添字の誤りも検出する。
                assert(left == M(i == j) && right == M(i == j));
              }
            }
          }
        }
      }
    }
  }
}
