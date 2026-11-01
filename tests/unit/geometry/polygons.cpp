// Verify: geometry/polygon.hpp
// Verify: geometry/line.hpp
// 凸包は全点を見渡すJarvis march、内外判定は全辺の半平面、直径は全点対を期待値にする。
#include <bits/stdc++.h>
using namespace std;
#include "geometry/polygon.hpp"
#include "geometry/line.hpp"

Polygon gift_wrap(Polygon points) {
  sort(points.begin(), points.end());
  points.erase(unique(points.begin(), points.end()), points.end());
  if (points.size() <= 2) {
    return points;
  }
  Polygon result;
  int u = 0;
  do {
    result.push_back(points[u]);
    int v = (u + 1) % points.size();
    for (int w = 0; w < (int)points.size(); ++w) {
      Real turn = (points[v].x - points[u].x) * (points[w].y - points[u].y) -
                  (points[v].y - points[u].y) * (points[w].x - points[u].x);
      auto length = [&](int i) {
        Real x = points[i].x - points[u].x;
        Real y = points[i].y - points[u].y;
        return x * x + y * y;
      };
      if (turn < 0 || (turn == 0 && length(w) > length(v))) {
        v = w;
      }
    }
    u = v;
  } while (u != 0);
  return result;
}

int main() {
  mt19937 rng(1802);
  for (int trial = 0; trial < 1000; ++trial) {
    Polygon points(trial % 31);
    for (auto& p : points) {
      p = Point((int)(rng() % 11) - 5, (int)(rng() % 11) - 5);
    }
    auto expected = gift_wrap(points);
    auto hull = convex_hull(points);
    // 別方式の全点走査で選んだ凸包と、頂点順序まで一致する。
    assert(hull == expected);
    if (hull.size() < 3) {
      continue;
    }
    Real largest = 0;
    for (auto p : points) {
      for (auto q : points) {
        largest = max(largest, norm(p - q));
      }
    }
    auto [u, v] = convex_polygon_diameter(hull);
    assert(norm(hull[u] - hull[v]) == largest);
    for (int x = -7; x <= 7; ++x) {
      for (int y = -7; y <= 7; ++y) {
        Point p(x, y);
        bool outside = false;
        bool boundary = false;
        for (int i = 0; i < (int)hull.size(); ++i) {
          Real side = cross(hull[(i + 1) % hull.size()] - hull[i], p - hull[i]);
          outside |= side < 0;
          boundary |= side == 0;
        }
        int location = outside ? 0 : boundary ? 1 : 2;
        // 凸多角形の全辺の左側にあるかを調べ、一般版と二分探索版の両方を比較する。
        assert(contains_polygon(hull, p) == location && contains_convex(hull, p) == location);
      }
    }
    auto with_boundary = convex_hull<true>(points);
    set<Point> expected_boundary;
    for (auto p : points) {
      if (contains_polygon(hull, p) == 1) {
        expected_boundary.insert(p);
      }
    }
    assert(set<Point>(with_boundary.begin(), with_boundary.end()) == expected_boundary);
  }
  Polygon l_shape{{0, 0}, {4, 0}, {4, 1}, {1, 1}, {1, 4}, {0, 4}};
  // 非凸なL字を2長方形の和集合として評価し、面積も分解して求める。
  assert(area(l_shape) == 7);
  for (int x = -2; x <= 10; ++x) {
    for (int y = -2; y <= 10; ++y) {
      Point p(x / 2.0L, y / 2.0L);
      bool inside = 0 < p.x && p.x < 4 && 0 < p.y && p.y < 4 && (p.x < 1 || p.y < 1);
      bool boundary = false;
      for (int i = 0; i < 6; ++i) {
        auto a = l_shape[i];
        auto b = l_shape[(i + 1) % 6];
        if (cross(b - a, p - a) == 0 && dot(p - a, p - b) <= 0) {
          boundary = true;
        }
      }
      assert(contains_polygon(l_shape, p) == (boundary ? 1 : inside ? 2 : 0));
    }
  }
  Polygon square{{0, 0}, {4, 0}, {4, 3}, {0, 3}};
  for (int x = -1; x <= 5; ++x) {
    auto cut = convex_polygon_cut(square, Line(Point(x, 4), Point(x, -1)));
    // 下向きの直線の左側（x以上）に残る長方形の面積を直接計算する。
    assert(abs(area(cut) - 3 * max(0, 4 - max(0, x))) < 1e-9);
  }
}
