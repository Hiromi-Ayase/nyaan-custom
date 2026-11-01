// Verify: geometry/integer-geometry.hpp
// 整数点の凸包を全点からの支持線で調べ、偏角順はatan2、内積・外積は128ビット式で照合する。
#include <bits/stdc++.h>
using namespace std;
#include "geometry/integer-geometry.hpp"

int main() {
  mt19937 rng(1803);
  for (int trial = 0; trial < 1000; ++trial) {
    Points points;
    for (int i = 0; i < trial % 31; ++i) {
      points.emplace_back((int)(rng() % 21) - 10, (int)(rng() % 21) - 10);
    }
    auto hull = ConvexHull(points);
    set<Point> input(points.begin(), points.end());
    // 凸包は入力点だけで構成され、重複がない。
    assert(set<Point>(hull.begin(), hull.end()).size() == hull.size());
    for (auto p : hull) {
      assert(input.count(p));
    }
    if (hull.size() >= 3) {
      for (int i = 0; i < (int)hull.size(); ++i) {
        auto a = hull[i];
        auto b = hull[(i + 1) % hull.size()];
        // 全辺が支持線となり、全入力点が左側にある。3頂点が同一直線に並ばない。
        for (auto p : points) {
          assert((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x) >= 0);
        }
        assert(ccw(a, b, hull[(i + 2) % hull.size()]) == 1);
      }
    } else if (hull.size() == 2) {
      for (auto p : points) {
        assert(ccw(hull[0], hull[1], p) == 0);
      }
    }
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    auto lower = LowerHull(points);
    auto upper = UpperHull(points);
    for (int i = 1; i < (int)lower.size(); ++i) {
      for (auto p : points) {
        assert(ccw(lower[i - 1], lower[i], p) >= 0);
      }
    }
    for (int i = 1; i < (int)upper.size(); ++i) {
      for (auto p : points) {
        assert(ccw(upper[i - 1], upper[i], p) <= 0);
      }
    }
    points.erase(remove(points.begin(), points.end(), Point(0, 0)), points.end());
    ArgumentSort(points);
    long double previous = -acosl(-1);
    for (auto p : points) {
      long double angle = atan2l((long double)p.y, (long double)p.x);
      // 異なる半平面と同方向の点も含め、偏角が単調非減少になる。
      assert(angle + 1e-15 >= previous);
      previous = angle;
    }
  }
  Point a(4000000000LL, -3000000000LL);
  Point b(-5000000000LL, 7000000000LL);
  // 64ビットを越える積を含むケースでも、128ビットで正しい内積・外積を返す。
  assert(dot(a, b) ==
         __int128_t(-4000000000LL) * 5000000000LL - __int128_t(3000000000LL) * 7000000000LL);
  assert(cross(a, b) ==
         __int128_t(4000000000LL) * 7000000000LL - __int128_t(3000000000LL) * 5000000000LL);
  assert((a + b) - b == a && -(-a) == a);
}
