// Verify: graph/chromatic-number.hpp
// Verify: graph/max-independent-set.hpp
// 全頂点部分集合による独立集合と、頂点を1つずつ彩色する全探索を期待値にする。
#include <bits/stdc++.h>
using namespace std;
#include "graph/chromatic-number.hpp"
#include "graph/max-independent-set.hpp"

int main() {
  mt19937 rng(903);
  for (int n = 0; n <= 10; ++n) {
    for (int trial = 0; trial < 80; ++trial) {
      vector<vector<int>> g(n);
      vector<pair<int, int>> edges;
      for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
          if (rng() % 4 <= trial % 4) {
            g[u].push_back(v);
            g[v].push_back(u);
            edges.emplace_back(u, v);
          }
        }
      }
      int largest = 0;
      for (int mask = 0; mask < (1 << n); ++mask) {
        bool valid = true;
        for (auto [u, v] : edges) {
          if ((mask >> u & 1) && (mask >> v & 1)) {
            valid = false;
          }
        }
        if (valid) {
          largest = max(largest, __builtin_popcount((unsigned)mask));
        }
      }
      auto independent = max_independent_set<64>(g);
      // 最大サイズだけでなく、重複と集合内部の辺がないことも確認する。
      assert((int)independent.size() == largest);
      set<int> chosen(independent.begin(), independent.end());
      assert(chosen.size() == independent.size());
      for (auto [u, v] : edges) {
        assert(!(chosen.count(u) && chosen.count(v)));
      }
      int chromatic = n;
      vector<int> colors(n, -1);
      auto dfs = [&](auto&& self, int u, int used) -> void {
        if (used >= chromatic) {
          return;
        }
        if (u == n) {
          chromatic = used;
          return;
        }
        for (int c = 0; c <= used; ++c) {
          bool valid = true;
          for (int v : g[u]) {
            if (colors[v] == c) {
              valid = false;
            }
          }
          if (valid) {
            colors[u] = c;
            self(self, u + 1, max(used, c + 1));
            colors[u] = -1;
          }
        }
      };
      dfs(dfs, 0, 0);
      // 空グラフ・完全グラフも含め、実際に可能な彩色の最小色数と比較する。
      assert(ChromaticNumber(g) == chromatic);
    }
  }
}
