// Verify: string/suffix-array.hpp
// 空接尾辞を含む全接尾辞をsubstrでソートし、SAと隣接LCPを比較する。
// 検索範囲は各接尾辞の先頭一致を全走査して求める。構築が元の文字列を変更しないことも確認する。
#include <bits/stdc++.h>
using namespace std;
#include "string/suffix-array.hpp"

int main() {
  mt19937 rng(123);
  for (int n = 0; n <= 70; ++n) {
    for (int trial = 0; trial < 15; ++trial) {
      string s(n, 'a');
      if (trial) {
        for (char& c : s) {
          c += rng() % 4;
        }
      }

      string original = s;
      vector<int> expected(n + 1);
      iota(expected.begin(), expected.end(), 0);
      sort(expected.begin(), expected.end(),
           [&](int a, int b) { return s.substr(a) < s.substr(b); });
      SuffixArray sa(s);

      // 空接尾辞を含めて文字列そのものをソートした順序と一致し、入力文字列も変更しない。
      assert(s == original && sa.sa == expected && sa.size() == n + 1);
      LCPArray lcp(sa);
      for (int i = 0; i < n; ++i) {
        int a = expected[i];
        int b = expected[i + 1];
        int common = 0;
        while (max(a, b) + common < n && s[a + common] == s[b + common]) {
          ++common;
        }

        // ソート順で隣り合う接尾辞を1文字ずつ比べたLCP長と一致する。
        assert(lcp.LCP[i] == common);
      }

      if (!n) {
        continue;
      }

      StringSearch search(lcp);
      for (int q = 0; q < 50; ++q) {
        string pattern(1 + rng() % 8, 'a');
        for (char& c : pattern) {
          c += rng() % 4;
        }

        vector<int> matches;
        for (int i = 0; i <= n; ++i) {
          if (s.compare(sa[i], pattern.size(), pattern) == 0) {
            matches.push_back(i);
          }
        }

        auto got = search.find(pattern);
        auto range =
            matches.empty() ? make_pair(-1, -1) : make_pair(matches.front(), matches.back());

        // 全接尾辞で前方一致を調べた範囲と照合し、見つからない場合の(-1, -1)も確認する。
        assert(got == range);
      }
    }
  }
}
