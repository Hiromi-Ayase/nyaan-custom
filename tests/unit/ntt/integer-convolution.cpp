// Verify: ntt/karatsuba.hpp
// Verify: ntt/schoenhage-strassen-radix2.hpp
// 正負の整数係数の積を二重ループで求め、非対称な長さ・再帰の切替・零係数を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "ntt/karatsuba.hpp"
#include "ntt/schoenhage-strassen-radix2.hpp"

int main() {
  mt19937 rng(9041);
  Schoenhage_Strassen_radix2<long long> ss;
  vector<int> lengths{1, 2, 7, 31, 32, 33, 41, 63, 64, 65, 129, 257};
  for (int n : lengths) {
    for (int m : lengths) {
      vector<long long> a(n);
      vector<long long> b(m);
      for (auto& x : a) {
        x = int(rng() % 21) - 10;
      }
      for (auto& x : b) {
        x = int(rng() % 21) - 10;
      }
      vector<long long> expected(n + m - 1);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          expected[i + j] += a[i] * b[j];
        }
      }
      // Karatsubaの分割や減算を使わずに求めた係数と、全係数を照合する。
      assert(karatsuba(a, b) == expected);

      auto [got, scale] = ss.multiply(a, b);
      // Schönhage-Strassen版は、2の冪のスケールを別途返す。
      assert(got.size() == expected.size());
      for (int k = 0; k < (int)got.size(); ++k) {
        // 負の値のシフトを避け、期待値に返されたスケールを掛けて比較する。
        assert(got[k] == expected[k] * (1LL << scale));
      }
    }
  }
}
