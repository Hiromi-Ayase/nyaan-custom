// Verify: string/wildcard-pattern-matching.hpp
// 各配置を一文字ずつ照合し、どちらかがワイルドカードなら一致とする。
// 空パターン・対象より長いパターン・全ワイルドカード・畳み込みの分岐を跨ぐ長さを含める。
#include <bits/stdc++.h>
using namespace std;
#include "string/wildcard-pattern-matching.hpp"

int main() {
  mt19937 rng(442);
  for (int n : {0, 1, 2, 7, 31, 64, 129, 257}) {
    for (int m : {0, 1, 2, 7, 31, 64, 129, 258}) {
      for (int trial = 0; trial < 8; ++trial) {
        string s(n, '*');
        string p(m, '*');
        if (trial) {
          for (char& c : s) {
            c = "*abc"[rng() % 4];
          }

          for (char& c : p) {
            c = "*abc"[rng() % 4];
          }
        }

        vector<int> expected;
        for (int i = 0; i + m <= n; ++i) {
          bool ok = true;
          for (int j = 0; j < m; ++j) {
            if (s[i + j] != '*' && p[j] != '*' && s[i + j] != p[j]) {
              ok = false;
            }
          }

          expected.push_back(ok);
        }

        // 全開始位置で各文字を直接比較した結果と照合する。両側のワイルドカードを許す。
        assert(wildcard_pattern_matching(s, p, '*') == expected);
      }
    }
  }
}
