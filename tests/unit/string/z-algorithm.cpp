// Verify: string/z-algorithm.hpp
// 長さ12以下の全二値文字列を列挙し、各位置から一文字ずつ比較したLCPと照合する。
// 空列・同一文字・周期列を含み、整数列でも同じ結果になることを確認する。
#include <bits/stdc++.h>
using namespace std;
#include "string/z-algorithm.hpp"

int main() {
  // All binary strings include empty, unary, alternating and periodic strings.
  for (int n = 0; n <= 12; ++n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
      string s(n, 'a');
      for (int i = 0; i < n; ++i) {
        s[i] += (mask >> i) & 1;
      }

      vector<int> expected(n);
      for (int i = 0; i < n; ++i) {
        while (i + expected[i] < n && s[expected[i]] == s[i + expected[i]]) {
          ++expected[i];
        }
      }

      // 各位置から1文字ずつ比べた共通接頭辞長と一致する。空文字列も対象にする。
      assert(z_algorithm(s) == expected);
      vector<int> a(s.begin(), s.end());
      for (int& x : a) {
        x = x == 'a' ? -1000000000 : 1000000000;
      }

      // 文字を大きな正負の整数に置き換えても、一致関係が同じならZ配列は変わらない。
      assert(z_algorithm(a) == expected);
    }
  }
}
