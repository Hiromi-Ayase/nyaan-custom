// Verify: marathon/top-k.hpp
// Verify: marathon/log_table.hpp
// Verify: marathon/multi-armed-bandit.hpp
// Top Kは全履歴の重複除去・ソート、対数表は直接log、バンディットは報酬の集計を期待値にする。
#include <bits/stdc++.h>
using namespace std;
#include "marathon/top-k.hpp"
#include "marathon/log_table.hpp"
#include "marathon/multi-armed-bandit.hpp"

using Entry = pair<int, int>;

unsigned long long key(const Entry& entry) {
  return entry.second % 30;
}

int main() {
  mt19937 rng(1601);
  for (int k : {1, 2, 3, 7, 17, 40}) {
    Top_K<Entry, key> top(k);
    map<int, Entry> best;
    for (int step = 0; step < 2000; ++step) {
      Entry candidate{(int)(rng() % 10000) - 5000, (int)(rng() % 90)};
      int hash = key(candidate);
      if (!best.count(hash) || candidate < best[hash]) {
        best[hash] = candidate;
      }
      top.insert(candidate);
      if (step % 13 == 0) {
        vector<Entry> expected;
        for (auto [h, value] : best) {
          expected.push_back(value);
        }
        sort(expected.begin(), expected.end());
        if ((int)expected.size() > k) {
          expected.resize(k);
        }
        auto actual = top.get();
        sort(actual.begin(), actual.end());
        // 同じhashには最小要素だけを残し、その上で全履歴の最小K個と一致する。
        assert(actual == expected);
      }
    }
  }
  log_table logs;
  unsigned long long state = 88172645463325252ULL;
  for (int i = 0; i < log_table::M; ++i) {
    state ^= state << 7;
    state ^= state >> 9;
    double expected = log((long double)state / ldexp(1.0L, 64));
    // 対数の引き算で作った表を、比を先に求める直接logと比較する。
    assert(abs(logs(i) - expected) < 1e-12 && logs(i) <= 0);
    assert(logs(i) == logs(i + log_table::M));
  }
  for (int n = 1; n <= 8; ++n) {
    MultiArmedBandit bandit(n);
    vector<long long> counts(n);
    vector<double> rewards(n);
    for (int step = 0; step < 1000; ++step) {
      int arm = bandit.play();
      // 探索期間は各腕を5回ずつ選び、その後も範囲内の腕だけを返す。
      assert(0 <= arm && arm < n);
      if (step < n * 5) {
        assert(arm == (step + 1) % n);
      }
      double reward = 1 + arm + step % 3;
      ++counts[arm];
      rewards[arm] += reward;
      bandit.reward(reward);
      assert(bandit.last == -1 && bandit.num == counts && bandit.v == rewards);
      if (step + 1 >= n * 5) {
        int expected = 0;
        for (int i = 1; i < n; ++i) {
          if (rewards[i] / counts[i] > rewards[expected] / counts[expected]) {
            expected = i;
          }
        }
        // 正の共通温度でexpは単調なので、bestは平均報酬が最大の腕となる。
        assert(bandit.best() == expected);
      }
    }
  }
}
