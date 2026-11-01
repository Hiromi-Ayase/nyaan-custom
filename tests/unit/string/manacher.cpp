// Verify: string/manacher.hpp
// 全二値文字列について、部分文字列を左右から比較して回文か判定する。
// 奇数長の半径、偶数長も含む極大回文、各右端に対する最左端を全探索で照合する。
#include <bits/stdc++.h>
using namespace std;
#include "string/manacher.hpp"

int main() {
  // 空文字列には回文の中心がないので、半径の列も空になる。
  assert(manacher(string()).empty());
  // 回文区間の列挙APIは、空でない列を受け取る。
  for (int n = 1; n <= 11; ++n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
      string s(n, 'a');
      for (int i = 0; i < n; ++i) {
        s[i] += (mask >> i) & 1;
      }

      auto palindrome = [&](int l, int r) {
        --r;
        while (l < r) {
          if (s[l] != s[r]) {
            return false;
          }

          ++l;
          --r;
        }

        return true;
      };
      vector<int> odd(n);
      vector<int> leftmost(n);
      vector<pair<int, int>> intervals;
      for (int center = 0; center < 2 * n - 1; ++center) {
        int best_l = center / 2 + (center & 1);
        int best_r = center / 2 + 1;
        for (int l = 0; l <= n; ++l) {
          int r = center + 1 - l;
          if (l <= r && r <= n && palindrome(l, r) && r - l > best_r - best_l) {
            best_l = l;
            best_r = r;
          }
        }

        intervals.emplace_back(best_l, best_r);
        if (!(center & 1)) {
          odd[center / 2] = (best_r - best_l + 1) / 2;
        }
      }

      for (int r = 0; r < n; ++r) {
        int l = 0;
        while (!palindrome(l, r + 1)) {
          ++l;
        }

        leftmost[r] = l;
      }

      // 全区間を左右から比較して求めた、各文字を中心とする最大の奇数長回文と照合する。
      assert(manacher(s) == odd);

      // 文字間の中心も含め、左右にこれ以上伸ばせない回文の半開区間と照合する。
      assert(enumerate_palindromes(s) == intervals);

      // 各終端に対して最も左から始まる回文を、全区間の列挙結果と照合する。
      assert(enumerate_leftmost_palindromes(s) == leftmost);
    }
  }
}
