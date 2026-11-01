// Verify: misc/rng.hpp
// Verify: misc/timer.hpp
// 固定シードの乱数列と区間・集合・シャッフルの不変条件を調べ、タイマーは基準時刻を直接ずらす。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "misc/rng.hpp"
#include "misc/timer.hpp"

int main() {
  unsigned long long state = internal::deterministic_seed();
  for (int i = 0; i < 1000; ++i) {
    state ^= state << 7;
    state ^= state >> 9;
    // 固定シードなら、公開されたXorshiftの状態遷移が毎回再現する。
    assert(my_rand::rng() == state);
  }
  for (int trial = 0; trial < 1000; ++trial) {
    long long l = trial % 21 - 10;
    long long r = l + 1 + trial % 30;
    auto closed = my_rand::rng(l, r);
    auto open = my_rand::randint(l, r);
    // 閉区間・半開区間を区別し、退化した閉区間も確認する。
    assert(l <= closed && closed <= r && l <= open && open < r);
    assert(my_rand::rng(l, l) == l);
    auto values = my_rand::randset(l, r, trial % (r - l + 1));
    assert((int)values.size() == trial % (r - l + 1));
    assert(set<long long>(values.begin(), values.end()).size() == values.size());
    for (auto x : values) {
      assert(l <= x && x < r);
    }
    auto shuffled = values;
    my_rand::randshf(shuffled);
    sort(shuffled.begin(), shuffled.end());
    // シャッフルは多重集合を保存する。
    assert(shuffled == values);
    double x = my_rand::rnd();
    double y = my_rand::rnd(-3.5, 7.25);
    assert(0 <= x && x < 1 && -3.5 <= y && y < 7.25);
  }
  Timer timer;
  timer.st -= chrono::seconds(5);
  // 実時間のsleepに頼らず、開始時刻を5秒戻してミリ秒単位への換算を確認する。
  auto before = timer.elapsed();
  assert(before >= 5000);
  timer.reset();
  auto after = timer();
  assert(after >= 0 && after < before);
}
