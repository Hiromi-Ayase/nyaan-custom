// Verify: string/suffix-automaton.hpp
// 全ての部分文字列をsetで列挙し、異なる部分文字列数と検索結果を照合する。
// 空文字・反復文字・未出現文字を含め、複数インスタンスの連続構築も検証する。
#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;
#include "string/suffix-automaton.hpp"

int main() {
  mt19937 rng(901);
  for (int n = 0; n <= 40; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      string s(n, 'a');
      for (char& c : s) {
        c += rng() % 4;
      }

      SuffixAutomaton<> sam(s);
      set<string> subs;
      for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
          subs.insert(s.substr(l, r - l));
        }
      }

      long long count = 0;
      for (int i = 1; i < sam.size(); ++i) {
        count += sam[i].len - sam[sam.link(i)].len;
      }

      // 全ての部分文字列をsetに入れて重複除去した個数と、状態から計算した個数を比べる。
      assert(count == (long long)subs.size());
      for (auto& sub : subs) {
        // 実在する部分文字列は全て検索できる。空文字列も初期状態として扱える。
        assert(sam.find(sub) >= 0);
      }

      for (int q = 0; q < 40; ++q) {
        string p(1 + rng() % 10, 'a');
        for (char& c : p) {
          c += rng() % 5;
        }

        // ランダムな検索語について、全列挙した集合への所属と検索の成否が一致する。
        assert((sam.find(p) >= 0) == bool(subs.count(p)));
      }
    }
  }
}
