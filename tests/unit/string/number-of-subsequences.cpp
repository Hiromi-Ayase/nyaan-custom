// Verify: string/number-of-subsequences.hpp
// 添字集合をビット全探索し、実際の部分列をsetに格納して重複を除いた個数と比較する。
// 空列・全要素同一・負数を含む列を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "string/number-of-subsequences.hpp"

int main() {
  mt19937 rng(887);
  for (int n = 0; n <= 14; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      vector<int> a(n);
      for (int& x : a) {
        x = trial == 0 ? 42 : int(rng() % 4) - 2;
      }

      set<vector<int>> expected;
      for (int mask = 1; mask < (1 << n); ++mask) {
        vector<int> sub;
        for (int i = 0; i < n; ++i) {
          if ((mask >> i) & 1) {
            sub.push_back(a[i]);
          }
        }

        expected.insert(sub);
      }

      // 全ての添字部分集合から作った列をsetで重複除去し、空列を含む異なる部分列数を比べる。
      assert((number_of_subsequences<vector<int>, long long>(a) == (long long)expected.size()));
    }
  }
}
