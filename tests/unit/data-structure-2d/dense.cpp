// Verify: data-structure-2d/2d-binary-indexed-tree.hpp
// Verify: data-structure-2d/2d-cumulative-sum.hpp
// Verify: data-structure-2d/2d-segment-tree.hpp
// Verify: data-structure-2d/dynamic-binary-indexed-tree-2d.hpp
// 二重vectorへ直接更新し、全セルを走査する矩形和と比較する。閉区間・半開区間の違いも明示する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure-2d/2d-binary-indexed-tree.hpp"
#include "data-structure-2d/2d-cumulative-sum.hpp"
#include "data-structure-2d/2d-segment-tree.hpp"
#include "data-structure-2d/dynamic-binary-indexed-tree-2d.hpp"

int main() {
  mt19937 rng(1901);
  for (int h : {1, 2, 3, 8, 17}) {
    for (int w : {1, 2, 5, 16}) {
      vector<vector<long long>> a(h, vector<long long>(w));
      vector<vector<long long>> added(h, vector<long long>(w));
      BinaryIndexedTree2D<long long> bit(h, w);
      BinaryIndexedTree2D<long long> imos(h, w);
      DynamicFenwickTree2D<long long> dynamic(h, w);
      auto sum = [](long long a, long long b) { return a + b; };
      SegmentTree2D<long long, decltype(sum)> tree(h, w, sum, 0);
      for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
          a[y][x] = (int)(rng() % 21) - 10;
          tree.set(y, x, a[y][x]);
          bit.add(y, x, a[y][x]);
          dynamic.add(y, x, a[y][x]);
        }
      }
      tree.build();
      for (int step = 0; step < 300; ++step) {
        int y = rng() % h;
        int x = rng() % w;
        long long delta = (int)(rng() % 101) - 50;
        a[y][x] += delta;
        bit.add(y, x, delta);
        dynamic.add(y, x, delta);
        tree.update(y, x, a[y][x]);
        int yl = rng() % (h + 1);
        int yr = rng() % (h + 1);
        int xl = rng() % (w + 1);
        int xr = rng() % (w + 1);
        if (yl > yr) {
          swap(yl, yr);
        }
        if (xl > xr) {
          swap(xl, xr);
        }
        long long expected = 0;
        for (int i = yl; i < yr; ++i) {
          for (int j = xl; j < xr; ++j) {
            expected += a[i][j];
          }
        }
        // BITの閉区間と他の半開区間を揃え、空矩形・端のセルも全走査と比較する。
        assert(bit.sum(yl, xl, yr - 1, xr - 1) == expected);
        assert(dynamic.sum(yl, xl, yr, xr) == expected && tree.query(yl, xl, yr, xr) == expected);
        assert(tree.get(y, x) == a[y][x] && tree(y, x) == a[y][x]);
        if (yl < yr && xl < xr) {
          imos.imos(yl, xl, yr - 1, xr - 1, delta);
          for (int i = yl; i < yr; ++i) {
            for (int j = xl; j < xr; ++j) {
              added[i][j] += delta;
            }
          }
        }
        // 閉矩形へのimos更新後は、prefix sumがそのセルの値になる。
        assert(imos.sum(y, x) == added[y][x]);
      }
      CumulativeSum2D<long long> prefix(h, w);
      CumulativeSum2D<long long> rectangles(h, w);
      vector<vector<long long>> expected_added(h, vector<long long>(w));
      for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
          prefix.add(y, x, a[y][x]);
        }
      }
      for (int step = 0; step < 100; ++step) {
        int yl = rng() % (h + 1);
        int yr = rng() % (h + 1);
        int xl = rng() % (w + 1);
        int xr = rng() % (w + 1);
        if (yl > yr) {
          swap(yl, yr);
        }
        if (xl > xr) {
          swap(xl, xr);
        }
        long long delta = (int)(rng() % 21) - 10;
        rectangles.imos(yl, xl, yr, xr, delta);
        for (int y = yl; y < yr; ++y) {
          for (int x = xl; x < xr; ++x) {
            expected_added[y][x] += delta;
          }
        }
      }
      prefix.build();
      rectangles.build();
      for (int yl = 0; yl <= h; ++yl) {
        for (int yr = yl; yr <= h; ++yr) {
          for (int xl = 0; xl <= w; ++xl) {
            for (int xr = xl; xr <= w; ++xr) {
              long long expected = 0;
              for (int y = yl; y < yr; ++y) {
                for (int x = xl; x < xr; ++x) {
                  expected += a[y][x];
                }
              }
              // 静的累積和は全ての矩形で確認し、build前に足した値を正しく保持する。
              assert(prefix.query(yl, xl, yr, xr) == expected);
            }
          }
        }
      }
      for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
          assert(rectangles.imos_get(y, x) == expected_added[y][x]);
        }
      }
      for (auto p : dynamic.bit) {
        delete p;
      }
    }
  }
}
