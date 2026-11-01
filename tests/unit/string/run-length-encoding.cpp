// Verify: string/run-length-encoding.hpp
// 各連続区間を先頭から走査した結果と比較する。
// 空列・一要素・全要素同一・負の整数・ブロック境界付近の長さを整数列と文字列で確認する。
#include <bits/stdc++.h>
using namespace std;
#include "string/run-length-encoding.hpp"

int main() {
  mt19937 rng(78123);
  for (int n : {0, 1, 2, 3, 31, 32, 33, 200}) {
    for (int trial = 0; trial < 100; ++trial) {
      vector<int> a(n);
      for (int& x : a) {
        x = trial == 0 ? -7 : int(rng() % 5) - 2;
      }

      vector<pair<int, int>> expected;
      for (int l = 0; l < n;) {
        int r = l + 1;
        while (r < n && a[r] == a[l]) {
          ++r;
        }

        expected.emplace_back(a[l], r - l);
        l = r;
      }

      // 同じ値の連続区間を左から走査して作った「値・長さ」の列と比較する。
      assert(RunLengthEncoding(a) == expected);
      string s;
      for (int x : a) {
        s += char(x + 'm');
      }

      vector<pair<char, int>> chars;
      for (auto [x, count] : expected) {
        chars.emplace_back(char(x + 'm'), count);
      }

      // 整数列を文字列に置き換えた場合も、区間の順序と長さが保存される。
      assert(RunLengthEncoding(s) == chars);
    }
  }
}
