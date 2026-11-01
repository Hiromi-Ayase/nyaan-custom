// Verify: data-structure-2d/segment-tree-on-range-tree.hpp
// 全点をmapに保持し、一点加算後の矩形和を全走査で求める。空集合・重複登録・64ビット座標を含む。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure-2d/segment-tree-on-range-tree.hpp"

long long sum_values(long long a, long long b) {
  return a + b;
}

long long zero() {
  return 0;
}

int main() {
  mt19937 rng(1902);
  for (int n : {0, 1, 2, 7, 31, 64, 65, 129}) {
    RangeTree<long long, long long, sum_values, zero> tree;
    map<pair<long long, long long>, long long> reference;
    vector<pair<long long, long long>> points;
    for (int i = 0; i < n; ++i) {
      long long x = (int)(rng() % 21) - 10;
      long long y = (int)(rng() % 31) - 15;
      if (i % 5 == 0) {
        x *= 100000000000LL;
        y *= 100000000000LL;
      }
      points.emplace_back(x, y);
      tree.add_point(x, y);
      tree.add_point(x, y);
      reference[{x, y}] = 0;
    }
    tree.build();
    for (int step = 0; step < 500; ++step) {
      if (n) {
        auto [x, y] = points[rng() % n];
        long long delta = (int)(rng() % 101) - 50;
        tree.add(x, y, delta);
        reference[{x, y}] += delta;
      }
      long long xl = (int)(rng() % 25) - 12;
      long long xr = (int)(rng() % 25) - 12;
      long long yl = (int)(rng() % 35) - 17;
      long long yr = (int)(rng() % 35) - 17;
      if (step % 3 == 0) {
        xl *= 100000000000LL;
        xr *= 100000000000LL;
        yl *= 100000000000LL;
        yr *= 100000000000LL;
      }
      if (xl > xr) {
        swap(xl, xr);
      }
      if (yl > yr) {
        swap(yl, yr);
      }
      long long expected = 0;
      for (auto [point, value] : reference) {
        auto [x, y] = point;
        if (xl <= x && x < xr && yl <= y && y < yr) {
          expected += value;
        }
      }
      // 重複して登録した座標は1点として更新され、負・巨大座標と半開境界もmapの全走査に一致する。
      assert(tree.sum(xl, yl, xr, yr) == expected);
    }
  }
}
