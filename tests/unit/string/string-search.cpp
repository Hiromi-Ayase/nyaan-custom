// Verify: string/string-search.hpp
// 全開始位置の組について一文字ずつLCPを求め、実際のsubstrの辞書順と比較する。
// 同じ開始位置・空区間・同一文字列・2の冪付近の長さを含める。
#include <bits/stdc++.h>
using namespace std;
#include "string/string-search.hpp"

int main() {
  mt19937 rng(993);
  for (int n : {1, 2, 3, 7, 16, 33, 64}) {
    for (int trial = 0; trial < 30; ++trial) {
      string s(n, 'a');
      if (trial) {
        for (char& c : s) {
          c += rng() % 4;
        }
      }

      StringSearch<string> search(s);
      for (int a = 0; a < n; ++a) {
        for (int c = 0; c < n; ++c) {
          int common = 0;
          while (max(a, c) + common < n && s[a + common] == s[c + common]) {
            ++common;
          }

          // 接尾辞を先頭から直接比較して求めた共通接頭辞長と一致する。
          assert(search.lcp(a, c) == common);
          string x = s.substr(a);
          string y = s.substr(c);

          // 接尾辞の辞書順の符号が、std::stringでの比較結果と一致する。
          assert(search.strcmp(a, c) == (x > y) - (x < y));
          int b = a + rng() % (n - a + 1);
          int d = c + rng() % (n - c + 1);
          x = s.substr(a, b - a);
          y = s.substr(c, d - c);

          // 部分文字列のLCPは、それぞれの区間の長さを超えない。
          assert(search.lcp(a, b, c, d) == min({common, b - a, d - c}));

          // 空区間を含む部分文字列の辞書順を、切り出した文字列の比較と照合する。
          assert(search.strcmp(a, b, c, d) == (x > y) - (x < y));
        }
      }
    }
  }
}
