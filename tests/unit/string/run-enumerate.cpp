// Verify: string/run-enumerate.hpp
// 全二値文字列の全区間について最小周期を直接調べ、左右に延長不能なrunを列挙する。
// 空文字・単一文字・複数の周期が重なる文字列で、欠落と重複の両方を検出する。
#include <bits/stdc++.h>
using namespace std;
#include "string/run-enumerate.hpp"

int main() {
  for (int n = 0; n <= 11; ++n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
      string s(n, 'a');
      for (int i = 0; i < n; ++i) {
        s[i] += (mask >> i) & 1;
      }

      vector<tuple<int, int, int>> expected;
      for (int l = 0; l < n; ++l) {
        for (int r = l + 2; r <= n; ++r) {
          int period = r - l;
          for (int p = 1; p < r - l; ++p) {
            bool ok = true;
            for (int i = l + p; i < r; ++i) {
              ok &= s[i] == s[i - p];
            }

            if (ok) {
              period = p;
              break;
            }
          }

          if (2 * period > r - l) {
            continue;
          }

          if (l > 0 && s[l - 1] == s[l - 1 + period]) {
            continue;
          }

          if (r < n && s[r] == s[r - period]) {
            continue;
          }

          expected.emplace_back(period, l, r);
        }
      }

      auto got = run_enumerate(s);
      sort(got.begin(), got.end());
      sort(expected.begin(), expected.end());

      // 最小周期と左右への延長不能性を全区間で判定し、極大反復区間の集合に漏れ・重複がないか調べる。
      assert(got == expected);
    }
  }
}
