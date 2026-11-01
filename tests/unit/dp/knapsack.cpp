// Verify: dp/knapsack01.hpp
// Verify: dp/branch-and-bound.hpp
// 全ての品物集合を列挙して、容量内の最大価値を期待値にする。重さは正とする。
// 空集合・容量0・全品物が入る容量・同価値/同重量を含め、値や重さを拡大してDP方式の切替も検証する。
#include <bits/stdc++.h>
using namespace std;
#include "dp/knapsack01.hpp"
#include "dp/branch-and-bound.hpp"

int main() {
  mt19937 rng(461);
  for (int n = 0; n <= 14; ++n) {
    for (int trial = 0; trial < 12; ++trial) {
      for (int mode = 0; mode < 3; ++mode) {
        vector<long long> v(n);
        vector<long long> w(n);
        for (int i = 0; i < n; ++i) {
          v[i] = (1 + rng() % 30) * (mode == 2 ? 1000003LL : 1);
          w[i] = (1 + rng() % 20) * (mode ? 1000033LL : 1);
        }

        long long total = accumulate(w.begin(), w.end(), 0LL);
        long long capacity = trial == 0 ? 0 : trial == 1 ? total : rng() % (total + 1);
        long long expected = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
          long long weight = 0;
          long long value = 0;
          for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
              weight += w[i];
              value += v[i];
            }
          }

          if (weight <= capacity) {
            expected = max(expected, value);
          }
        }

        BranchAndBound<long long, long long> solver(v, w);

        // 分枝限定法の最大価値を、全ての品物の部分集合を試した最適値と照合する。
        assert(solver.run(capacity) == expected);

        // サイズに応じて手法を選ぶ版も、同じ全探索の最適値と一致する。
        assert(knapsack01(v, w, capacity) == expected);
      }
    }
  }
}
