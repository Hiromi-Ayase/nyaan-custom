// Verify: matrix/matrix.hpp
// Verify: matrix/characteristric-polynomial.hpp
// 行列積は三重ループ、行列式と特性多項式は置換全列挙で照合する。非可換な積と0乗も試す。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "matrix/matrix.hpp"
#include "matrix/characteristric-polynomial.hpp"

using M = ModInt<101>;
using Mat = vector<vector<M>>;

Mat multiply(const Mat& a, const Mat& b) {
  Mat c(a.size(), vector<M>(b[0].size()));
  for (int i = 0; i < (int)c.size(); ++i) {
    for (int j = 0; j < (int)c[i].size(); ++j) {
      for (int k = 0; k < (int)b.size(); ++k) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}

int main() {
  mt19937 rng(602);
  // 0次の特性多項式は、空行列の行列式1である。
  assert(CharacteristicPolynomial(Mat{}) == vector<M>{1});
  for (int h = 1; h <= 5; ++h) {
    for (int w = 1; w <= 5; ++w) {
      for (int p = 1; p <= 5; ++p) {
        Matrix<M> a(h, p);
        Matrix<M> b(p, w);
        for (auto& row : a.A) {
          for (auto& x : row) {
            x = rng() % 101;
          }
        }
        for (auto& row : b.A) {
          for (auto& x : row) {
            x = rng() % 101;
          }
        }
        auto got = a * b;
        // 長方形の積は高さh・幅wになり、各成分が行と列の内積に一致する。
        assert(got.H() == h && got.W() == w && got.A == multiply(a.A, b.A));
        // 加算・減算を相殺すると、元の全成分が復元される。
        assert((got + got - got) == got);
      }
    }
  }

  for (int n = 1; n <= 5; ++n) {
    for (int trial = 0; trial < 60; ++trial) {
      Matrix<M> a(n);
      for (auto& row : a.A) {
        for (auto& x : row) {
          x = trial == 0 ? 0 : rng() % 101;
        }
      }
      vector<int> permutation(n);
      iota(permutation.begin(), permutation.end(), 0);
      vector<M> polynomial(n + 1);
      do {
        vector<M> term{1};
        for (int i = 0; i < n; ++i) {
          vector<M> next(term.size() + 1);
          for (int j = 0; j < (int)term.size(); ++j) {
            next[j] += term[j] * a[i][permutation[i]];
            if (permutation[i] == i) {
              next[j + 1] -= term[j];
            }
          }
          term = next;
          for (int j = 0; j < i; ++j) {
            if (permutation[j] > permutation[i]) {
              for (auto& x : term) {
                x = -x;
              }
            }
          }
        }
        for (int i = 0; i <= n; ++i) {
          polynomial[i] += term[i];
        }
      } while (next_permutation(permutation.begin(), permutation.end()));
      // det(A-xI)を置換全列挙と素朴な多項式積で求め、符号も含め全係数を比較する。
      assert(CharacteristicPolynomial(a.A) == polynomial);
      // 通常の行列式は、det(A-xI)の定数項に一致する。
      assert(a.determinant() == polynomial[0]);

      auto inverse = a.inverse();
      // 行列式が0のときだけ、逆行列APIは空の行列を返す。
      assert(inverse.A.empty() == (polynomial[0] == 0));
      if (!inverse.A.empty()) {
        // 独立した三重ループで掛けて、逆行列が単位行列を作ることを確認する。
        assert(multiply(a.A, inverse.A) == Matrix<M>::I(n).A);
      }
      auto expected = Matrix<M>::I(n).A;
      for (int exponent = 0; exponent <= 10; ++exponent) {
        // 繰り返し二乗法の結果を、1回ずつ掛けた行列と比較する。0乗も含む。
        assert((a ^ exponent).A == expected);
        expected = multiply(expected, a.A);
      }
    }
  }
}
