// Verify: data-structure-2d/rectangle-sum.hpp
// Verify: data-structure-2d/rectangle-add-rectangle-sum.hpp
// 静的点の和は全点走査、矩形加算の積分は追加矩形との重なり面積を直接足して求める。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure-2d/rectangle-sum.hpp"
#include "data-structure-2d/rectangle-add-rectangle-sum.hpp"

int main() {
  mt19937 rng(1903);
  for (int n : {0, 1, 2, 17, 65, 200}) {
    vector<long long> xs(n);
    vector<long long> ys(n);
    vector<long long> weights(n);
    for (int i = 0; i < n; ++i) {
      xs[i] = (int)(rng() % 21) - 10;
      ys[i] = (int)(rng() % 21) - 10;
      weights[i] = (int)(rng() % 101) - 50;
    }
    auto sum = [](long long a, long long b) { return a + b; };
    RectangleSum<long long, long long, decltype(sum)> points(xs, ys, weights, sum);
    for (int step = 0; step < 1000; ++step) {
      long long xl = (int)(rng() % 25) - 12;
      long long xr = (int)(rng() % 25) - 12;
      long long yl = (int)(rng() % 25) - 12;
      long long yr = (int)(rng() % 25) - 12;
      if (xl > xr) {
        swap(xl, xr);
      }
      if (yl > yr) {
        swap(yl, yr);
      }
      long long expected = 0;
      long long bottomless = 0;
      for (int i = 0; i < n; ++i) {
        if (xl <= xs[i] && xs[i] < xr && ys[i] < yr) {
          bottomless += weights[i];
          if (yl <= ys[i]) {
            expected += weights[i];
          }
        }
      }
      // 同座標の複数点は重みを全て数え、3引数版は負のyも下限なしに含む。
      assert(points.rect_sum(xl, yl, xr, yr) == expected);
      assert(points.rect_sum(xl, xr, yr) == bottomless);
    }
    delete[] points.seg.pool;
  }
  for (int trial = 0; trial < 100; ++trial) {
    RectangleAddRectangleSum<long long, long long> solver;
    vector<array<long long, 5>> rectangles;
    for (int i = 0; i < trial % 31; ++i) {
      long long xl = (int)(rng() % 101) - 50;
      long long xr = xl + rng() % 20;
      long long yl = (int)(rng() % 101) - 50;
      long long yr = yl + rng() % 20;
      long long value = (int)(rng() % 21) - 10;
      solver.add_rectangle(xl, xr, yl, yr, value);
      rectangles.push_back({xl, xr, yl, yr, value});
    }
    vector<long long> expected;
    for (int i = 0; i < 100; ++i) {
      long long xl = (int)(rng() % 121) - 60;
      long long xr = xl + rng() % 40;
      long long yl = (int)(rng() % 121) - 60;
      long long yr = yl + rng() % 40;
      solver.add_query(xl, xr, yl, yr);
      long long sum = 0;
      for (auto r : rectangles) {
        long long width = max(0LL, min(xr, r[1]) - max(xl, r[0]));
        long long height = max(0LL, min(yr, r[3]) - max(yl, r[2]));
        sum += width * height * r[4];
      }
      expected.push_back(sum);
    }
    // 空矩形・接するだけの矩形・重なる正負の更新も、交差面積の総和と一致する。
    assert(solver.solve() == expected);
    // solveはconstなので、同じクエリを再実行しても結果が変わらない。
    assert(solver.solve() == expected);
  }
}
