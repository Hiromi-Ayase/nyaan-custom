// Verify: geometry/geometry-base.hpp
// Verify: geometry/line.hpp
// Verify: geometry/segment.hpp
// Verify: geometry/circle.hpp
// 整数の行列式による交差判定、直線方程式からの射影、円の距離条件と交点の残差を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "geometry/geometry-base.hpp"
#include "geometry/line.hpp"
#include "geometry/segment.hpp"
#include "geometry/circle.hpp"

using I = pair<long long, long long>;

long long determinant(I a, I b, I c) {
  return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

bool on_segment(I a, I b, I p) {
  return determinant(a, b, p) == 0 && min(a.first, b.first) <= p.first &&
         p.first <= max(a.first, b.first) && min(a.second, b.second) <= p.second &&
         p.second <= max(a.second, b.second);
}

bool intersects(I a, I b, I c, I d) {
  if (on_segment(a, b, c) || on_segment(a, b, d) || on_segment(c, d, a) || on_segment(c, d, b)) {
    return true;
  }
  long long x = determinant(a, b, c);
  long long y = determinant(a, b, d);
  long long z = determinant(c, d, a);
  long long w = determinant(c, d, b);
  return (x < 0) != (y < 0) && (z < 0) != (w < 0) && x && y && z && w;
}

long double point_distance(I a, I b, I p) {
  long double vx = b.first - a.first;
  long double vy = b.second - a.second;
  long double t = ((p.first - a.first) * vx + (p.second - a.second) * vy) / (vx * vx + vy * vy);
  t = max(0.0L, min(1.0L, t));
  return hypotl(p.first - a.first - t * vx, p.second - a.second - t * vy);
}

bool close(Real a, Real b) {
  return abs(a - b) < 1e-8L * (1 + abs(b));
}

int main() {
  mt19937 rng(1801);
  auto random_point = [&]() { return I{(int)(rng() % 21) - 10, (int)(rng() % 21) - 10}; };
  for (int trial = 0; trial < 10000; ++trial) {
    I a = random_point();
    I b = random_point();
    I c = random_point();
    I d = random_point();
    if (a == b || c == d) {
      continue;
    }
    Segment first{Point(a), Point(b)};
    Segment second{Point(c), Point(d)};
    bool hit = intersects(a, b, c, d);
    // 浮動小数のEPSに頼らない整数行列式と、端点接触・共線の重なりを含めて比較する。
    assert(is_intersect_ss(first, second) == hit);
    assert(is_intersect_sp(first, Point(c)) == on_segment(a, b, c));
    Real expected = hit ? 0
                        : min({point_distance(a, b, c), point_distance(a, b, d),
                               point_distance(c, d, a), point_distance(c, d, b)});
    assert(close(distance_sp(first, Point(c)), point_distance(a, b, c)));
    assert(close(distance_ss(first, second), expected));
    Point p(a);
    Point q(b);
    // 基本演算を座標ごとの整数式と照合し、回転は既知の直角回転を使う。
    assert(dot(p, q) == a.first * b.first + a.second * b.second);
    assert(cross(p, q) == a.first * b.second - a.second * b.first);
    auto rotated = p.rotate(pi / 2);
    assert(close(rotated.x, -p.y) && close(rotated.y, p.x));
    assert(close(abs(p), hypotl(a.first, a.second)));
    long long A = (int)(rng() % 11) - 5;
    long long B = (int)(rng() % 11) - 5;
    long long C = (int)(rng() % 21) - 10;
    if (A == 0 && B == 0) {
      continue;
    }
    Line line(A, B, C);
    // 係数指定コンストラクタの2点はAx+By=Cを満たし、互いに異なる。
    assert(close(A * line.a.x + B * line.a.y, C) && close(A * line.b.x + B * line.b.y, C) &&
           abs(line.a - line.b) > 0);
    Real residual = (A * p.x + B * p.y - C) / (A * A + B * B);
    auto projected = projection(line, p);
    assert(close(projected.x, p.x - A * residual) && close(projected.y, p.y - B * residual));
    Line normal(p, p + Point(A, B));
    assert(is_orthogonal(line, normal));
    auto intersection = cross_point_ll(line, normal);
    assert(close(intersection.x, projected.x) && close(intersection.y, projected.y));
    Line shifted(line.a + Point(A, B), line.b + Point(A, B));
    assert(is_parallel(line, shifted) && !is_intersect_ll(line, shifted));
  }
  // ccwの共線上の5通りを、向きと位置の意味を持つ固定例で確認する。
  assert(ccw(Point(0, 0), Point(2, 0), Point(1, 1)) == 1);
  assert(ccw(Point(0, 0), Point(2, 0), Point(1, -1)) == -1);
  assert(ccw(Point(0, 0), Point(2, 0), Point(-1, 0)) == 2);
  assert(ccw(Point(0, 0), Point(2, 0), Point(3, 0)) == -2);
  assert(ccw(Point(0, 0), Point(2, 0), Point(1, 0)) == 0);
  for (int r1 = 1; r1 <= 10; ++r1) {
    for (int r2 = 1; r2 <= 10; ++r2) {
      for (int dx = 0; dx <= 22; ++dx) {
        for (int dy = 0; dy <= 5; ++dy) {
          if (dx == 0 && dy == 0) {
            continue;
          }
          int distance2 = dx * dx + dy * dy;
          int sum2 = (r1 + r2) * (r1 + r2);
          int difference2 = (r1 - r2) * (r1 - r2);
          int expected = distance2 > sum2           ? 4
                         : distance2 == sum2        ? 3
                         : distance2 > difference2  ? 2
                         : distance2 == difference2 ? 1
                                                    : 0;
          Circle a(Point(-3, 7), r1);
          Circle b(Point(dx - 3, dy + 7), r2);
          // 距離を平方して整数比較するため、接する境界でも平方根の丸めに依存しない。
          assert(intersect(a, b) == expected && intersect(b, a) == expected);
          if (1 <= expected && expected <= 3) {
            auto [p, q] = crosspoint(a, b);
            for (auto x : {p, q}) {
              assert(close(norm(x - a.p), r1 * r1) && close(norm(x - b.p), r2 * r2));
            }
            if (expected == 2) {
              assert(abs(p - q) > 1e-8);
            } else {
              assert(abs(p - q) < 1e-7);
            }
          }
        }
      }
    }
  }
}
