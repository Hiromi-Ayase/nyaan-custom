// Verify: data-structure/line-container.hpp
// Verify: data-structure/line-container-2d.hpp
// 追加した全ての直線・点をvectorに保持し、クエリごとに全走査して最小最大を求める。
// 傾きの重複、負の座標、x=0、二次元の片方または両方の係数が0の場合を含める。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/line-container.hpp"
#include "data-structure/line-container-2d.hpp"

int main() {
  mt19937 rng(7623);
  MinLineContainer<long long> lo;
  MaxLineContainer<long long> hi;
  LineContainer2D plane;
  vector<pair<long long, long long>> lines;
  for (int step = 0; step < 300; ++step) {
    long long a = int(rng() % 41) - 20;
    long long b = int(rng() % 101) - 50;
    lo.add(a, b);
    hi.add(a, b);
    plane.add(a, b);
    lines.emplace_back(a, b);
    for (long long x = -30; x <= 30; ++x) {
      long long mn = LLONG_MAX;
      long long mx = LLONG_MIN;
      for (auto [k, c] : lines) {
        mn = min(mn, k * x + c);
        mx = max(mx, k * x + c);
      }

      // 全ての直線を代入して求めた最小・最大値と比較する。同じ傾きの追加も対象にする。
      assert(lo.query(x) == mn && hi.query(x) == mx);
      for (long long y : {-7LL, 0LL, 11LL}) {
        mn = LLONG_MAX;
        mx = LLONG_MIN;
        for (auto [u, v] : lines) {
          mn = min(mn, x * u + y * v);
          mx = max(mx, x * u + y * v);
        }

        // 全ての登録点との内積を列挙して求めた最小・最大値と比較する。
        assert(plane.min_ll(x, y) == mn && plane.max_ll(x, y) == mx);

        // 浮動小数点版の最小内積が、整数で求めた値と許容誤差内で一致する。
        assert(abs(plane.min_ld(x, y) - mn) < 1e-8L);

        // 浮動小数点版の最大内積が、整数で求めた値と許容誤差内で一致する。
        assert(abs(plane.max_ld(x, y) - mx) < 1e-8L);
      }
    }
  }
}
