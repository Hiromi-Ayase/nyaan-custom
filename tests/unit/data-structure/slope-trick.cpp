// Verify: data-structure/slope-trick.hpp
// 整数座標ごとの関数値を配列として持ち、hinge/絶対値の加算・平行移動・片側min・mergeを愚直に計算する。
// 重み付き更新と負の座標を含め、各点の値と最小値・最小位置を確認する。
// 参照配列は十分な余白を取り、更新の影響が境界へ届かない中央領域で比較する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/slope-trick.hpp"

int main() {
  mt19937 rng(4391);
  const int radius = 1024;
  for (int trial = 0; trial < 25; ++trial) {
    SlopeTrick slope;
    vector<long long> f(2 * radius + 1);
    for (int step = 0; step < 80; ++step) {
      int op = rng() % 8;
      long long a = int(rng() % 41) - 20;
      long long c = 1 + rng() % 5;
      if (op <= 2) {
        if (op == 0) {
          slope.add_xma(a, c);
        }

        if (op == 1) {
          slope.add_amx(a, c);
        }

        if (op == 2) {
          slope.add_abs_xma(a, c);
        }

        for (int x = -radius; x <= radius; ++x) {
          f[x + radius] += c * (op == 0 ? max(0LL, x - a) : op == 1 ? max(0LL, a - x) : abs(x - a));
        }
      } else if (op == 3) {
        slope.shift_y(a);
        for (auto& v : f) {
          v += a;
        }
      } else if (op == 4) {
        a %= 4;
        slope.shift_x(a);
        auto old = f;
        for (int x = -radius; x <= radius; ++x) {
          int y = clamp<long long>(x - a, -radius, radius);
          f[x + radius] = old[y + radius];
        }
      } else if (op == 5) {
        slope.chmin_right();
        for (int i = 1; i < (int)f.size(); ++i) {
          f[i] = min(f[i], f[i - 1]);
        }
      } else if (op == 6) {
        slope.chmin_left();
        for (int i = (int)f.size() - 2; i >= 0; --i) {
          f[i] = min(f[i], f[i + 1]);
        }
      } else {
        SlopeTrick other;
        other.add_abs_xma(a, c);
        slope.merge(other);
        for (int x = -radius; x <= radius; ++x) {
          f[x + radius] += c * abs(x - a);
        }
      }

      for (int x = -100; x <= 100; ++x) {
        // 関数の加算・移動・片側最小化・merge後の値を、整数座標ごとに直接更新した表と比較する。
        assert(slope.eval(x) == f[x + radius]);
      }

      auto [x, y] = slope.get_min();

      // 返された最小値が、十分広い参照区間で全点を走査した最小値と一致する。
      assert(y == *min_element(f.begin() + 256, f.end() - 256));

      // 返された最小点に実際に代入すると、返された最小値を達成する。
      assert(slope.eval(x) == y);
    }
  }
}
