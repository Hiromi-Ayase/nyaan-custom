// Verify: dp/golden-section-search.hpp
// Verify: dp/monotone-minima.hpp
// Verify: dp/monge-shortest-path.hpp
// Verify: dp/monge-d-edge-shortest-path.hpp
// Verify: dp/monge-d-edge-shortest-path-enumerate.hpp
// Verify: dp/concave-min-plus-convolution.hpp
// 単峰関数の探索は全点走査、Monge最短路は全遷移のDP、min/max-plus畳み込みは二重ループと比較する。
// 負の座標、同率最適、辺数1/N、正負の辺定数、空配列と不均等な長さを含める。
#include <bits/stdc++.h>
using namespace std;
#include "dp/golden-section-search.hpp"
#include "dp/monotone-minima.hpp"
#include "dp/monge-shortest-path.hpp"
#include "dp/monge-d-edge-shortest-path.hpp"
#include "dp/monge-d-edge-shortest-path-enumerate.hpp"
#include "dp/concave-min-plus-convolution.hpp"

int main() {
  mt19937 rng(1983);
  for (int l = -20; l <= 10; ++l) {
    for (int r = l; r <= 20; ++r) {
      for (int c : {-25, -3, 0, 17, 25}) {
        function<long long(long long)> f = [=](long long x) { return (x - c) * (x - c); };
        auto [x, y] = golden_section_search<long long>(f, l, r);
        long long expected = LLONG_MAX;
        for (int i = l; i <= r; ++i) {
          expected = min(expected, f(i));
        }

        // 返された点が探索区間内にあり、全点走査で求めた最小値を実際に達成する。
        assert(l <= x && x <= r && y == expected && f(x) == y);
      }
    }
  }

  for (int n = 1; n <= 25; ++n) {
    for (int trial = 0; trial < 8; ++trial) {
      vector<long long> pos(n + 1);
      for (int i = 1; i <= n; ++i) {
        pos[i] = pos[i - 1] + 1 + rng() % 4;
      }

      long long bias = int(rng() % 41) - 20;
      function<long long(int, int)> cost = [&](int i, int j) {
        return (pos[j] - pos[i]) * (pos[j] - pos[i]) + bias;
      };
      const long long inf = (1LL << 62) - 1;
      vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, inf));
      dp[0][0] = 0;
      for (int d = 1; d <= n; ++d) {
        for (int j = 1; j <= n; ++j) {
          for (int i = 0; i < j; ++i) {
            if (dp[d - 1][i] != inf) {
              dp[d][j] = min(dp[d][j], dp[d - 1][i] + cost(i, j));
            }
          }
        }
      }

      auto all = enumerate_monge_d_edge_shortest_path(n, cost);
      auto best = monge_shortest_path<long long>(n, cost);
      for (int d = 1; d <= n; ++d) {
        // 全辺数を返す版の各結果を、辺数を状態に含めた全遷移DPと照合する。
        assert(all[d] == dp[d][n]);

        // 辺数を固定して求める版も、全遷移DPの「ちょうどd辺」の最適値と一致する。
        assert(monge_d_edge_shortest_path(n, d, 1000000, cost) == dp[d][n]);
      }

      for (int j = 0; j <= n; ++j) {
        long long expected = inf;
        for (int d = 0; d <= n; ++d) {
          expected = min(expected, dp[d][j]);
        }

        // 辺数制限のない最短路は、全遷移DPの全辺数のうち最小の値になる。
        assert(best[j] == expected);
      }

      auto argmin = monotone_minima<long long>(n + 1, n + 1, cost);
      for (int i = 0; i <= n; ++i) {
        long long expected = LLONG_MAX;
        for (int j = 0; j <= n; ++j) {
          expected = min(expected, cost(i, j));
        }

        // 各行の最小位置が、列を全て走査した最小値を達成する。
        assert(cost(i, argmin[i]) == expected);
      }
    }
  }

  for (int n = 0; n <= 30; ++n) {
    for (int m = 0; m <= 25; ++m) {
      vector<long long> a(n);
      vector<long long> b(m);
      long long slope = -20;
      for (int i = 1; i < n; ++i) {
        slope += rng() % 4;
        a[i] = a[i - 1] + slope;
      }

      for (auto& x : b) {
        x = int(rng() % 101) - 50;
      }

      vector<long long> expected(n && m ? n + m - 1 : 0, LLONG_MAX);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          expected[i + j] = min(expected[i + j], a[i] + b[j]);
        }
      }

      // min-plus畳み込みの全係数を、添字の全組合せを試した最小値と比較する。
      assert(concave_min_plus_convolution(a, b) == expected);
      for (auto& x : a) {
        x = -x;
      }

      for (auto& x : b) {
        x = -x;
      }

      for (auto& x : expected) {
        x = -x;
      }

      // 符号反転で得たmax-plus畳み込みを、同じ全探索の最大値と比較する。
      assert(concave_max_plus_convolution(a, b) == expected);
    }
  }
}
