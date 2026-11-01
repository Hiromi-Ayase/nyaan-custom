// Verify: segment-tree/li-chao-tree.hpp
// Verify: segment-tree/dynamic-li-chao-tree.hpp
// 追加した全直線・線分を保存し、各評価点で全て代入して最小値を求める。大きな座標と境界も試す。
#include <bits/stdc++.h>
using namespace std;
#include "segment-tree/li-chao-tree.hpp"
#include "segment-tree/dynamic-li-chao-tree.hpp"

int main() {
  constexpr long long inf = 1LL << 62;
  mt19937 rng(1205);
  for (long long base : {0LL, 1000000000000LL, -1000000000000LL}) {
    vector<long long> xs;
    for (int i = 0; i < 67; ++i) {
      xs.push_back(base + i * i);
    }
    auto shuffled = xs;
    shuffle(shuffled.begin(), shuffled.end(), rng);
    shuffled.push_back(xs[0]);
    LiChaoTree<long long, inf> fixed(shuffled);
    DynamicLiChaoTree<long long, inf> dynamic(xs.front(), xs.back());
    vector<array<long long, 4>> lines;
    for (int step = 0; step < 300; ++step) {
      for (int query = 0; query < 5; ++query) {
        int i = rng() % xs.size();
        long long x = xs[i];
        long long expected = inf;
        for (auto line : lines) {
          if (line[2] <= x && x <= line[3]) {
            expected = min(expected, line[0] * x + line[1]);
          }
        }
        // 未登録時のINF、重なる線分、同じ傾き、64ビット座標を全線走査と比較する。
        assert(fixed.query(x) == expected && fixed.query_idx(i) == expected);
        assert(dynamic.query(x) == expected);
      }
      long long a = (int)(rng() % 41) - 20;
      long long b = (int)(rng() % 101) - 50;
      long long l = xs[rng() % xs.size()];
      long long r = xs[rng() % xs.size()];
      if (l > r) {
        swap(l, r);
      }
      if (step % 3 == 0) {
        l = xs.front();
        r = xs.back();
        fixed.update(a, b);
        dynamic.update(a, b);
      } else {
        fixed.update_segment(a, b, l, r);
        dynamic.update_line_segment(a, b, l, r);
      }
      lines.push_back({a, b, l, r});
    }
  }
  // 40ビット幅の区間は、動的木の節点番号が32ビットを越えるケースを作る。
  DynamicLiChaoTree<long long, inf> wide(-(1LL << 39), (1LL << 39) - 1);
  vector<array<long long, 4>> segments{
      {2, 3, -(1LL << 39), 0}, {-3, 5, 1, (1LL << 39) - 1}, {0, -100, -10, 10}};
  for (auto line : segments) {
    wide.update_line_segment(line[0], line[1], line[2], line[3]);
  }
  for (long long x : {-(1LL << 39), -100LL, -10LL, 0LL, 1LL, 10LL, 100LL, (1LL << 39) - 1}) {
    long long expected = inf;
    for (auto line : segments) {
      if (line[2] <= x && x <= line[3]) {
        expected = min(expected, line[0] * x + line[1]);
      }
    }
    // 大きな木でも線分の両端を含む閉区間が正しく反映される。
    assert(wide.query(x) == expected);
  }
}
