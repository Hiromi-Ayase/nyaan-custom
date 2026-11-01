// Verify: string/aho-corasick.hpp
// 各パターンを全開始位置で直接比較し、重なりを含む出現回数を数える。
// heavy/light両方式について、重複パターン・接尾辞の包含・空の検索対象を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "string/aho-corasick.hpp"

int main() {
  mt19937 rng(12345);
  for (int trial = 0; trial < 200; ++trial) {
    AhoCorasick<3, 'a', false> light;
    AhoCorasick<3, 'a', true> heavy;
    vector<string> patterns{"a", "aa", "aaa", "aba", "a"};
    for (int i = 0; i < 15; ++i) {
      string s(1 + rng() % 8, 'a');
      for (char& c : s) {
        c += rng() % 3;
      }

      patterns.push_back(s);
    }

    for (int i = 0; i < (int)patterns.size(); ++i) {
      light.add(patterns[i], i);
      heavy.add(patterns[i], i);
    }

    light.build();
    heavy.build();
    for (int n : {0, 1, 2, 9, 100}) {
      string s(n, 'a');
      if (trial) {
        for (char& c : s) {
          c += rng() % 3;
        }
      }

      auto got = heavy.match(s);
      long long total = 0;
      for (int i = 0; i < (int)patterns.size(); ++i) {
        long long count = 0;
        for (int j = 0; j + (int)patterns[i].size() <= n; ++j) {
          count += s.compare(j, patterns[i].size(), patterns[i]) == 0;
        }

        // 各パターンの出現回数を、開始位置を全て試す直接比較と照合する。重なりも別々に数える。
        assert(got[i] == count);
        total += count;
      }

      // 軽量版の総マッチ数は、重複登録したパターンも含めた出現回数の総和になる。
      assert(light.match(s) == total);
    }
  }
}
