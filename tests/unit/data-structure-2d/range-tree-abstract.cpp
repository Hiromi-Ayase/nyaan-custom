// Verify: data-structure-2d/abstract-range-tree.hpp
// 全点をmapに保持し、一点加算後の矩形和を全走査で求める。空集合・重複登録・64ビット座標を含む。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure-2d/abstract-range-tree.hpp"

long long sum_values(long long a, long long b) {
  return a + b;
}

long long zero() {
  return 0;
}

int main() {
  mt19937 rng(1902);
  for (int n : {0, 1, 2, 7, 31, 64, 65, 129}) {
    // 抽象版の内部データ構造にもテスト用ライブラリを使わず、単純なvectorを渡す。
    auto make = [](int n) { return new vector<long long>(n); };
    auto add = [](vector<long long>& a, int i, long long value) { a[i] += value; };
    auto fold = [](vector<long long>& a, int l, int r) {
      long long sum = 0;
      for (int i = l; i < r; ++i) {
        sum += a[i];
      }
      return sum;
    };
    RangeTree<vector<long long>, long long, long long> tree(make, add, fold, sum_values, 0);

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
    for (auto p : tree.ds) {
      delete p;
    }
  }
}
