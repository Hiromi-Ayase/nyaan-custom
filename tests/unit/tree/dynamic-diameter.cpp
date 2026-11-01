// Verify: tree/dynamic-diameter.hpp
// 辺の重み変更ごとに全始点からDFSし、最大距離と返された両端の距離を調べる。
#include <bits/stdc++.h>
using namespace std;
#include "tree/dynamic-diameter.hpp"

int main() {
  mt19937 rng(1006);
  for (int n : {1, 2, 3, 7, 16, 31, 64}) {
    for (int shape = 0; shape < 3; ++shape) {
      WeightedGraph<long long> g(n);
      vector<pair<int, int>> edges;
      vector<vector<long long>> weight(n, vector<long long>(n));
      for (int u = 1; u < n; ++u) {
        int p = shape == 0 ? u - 1 : shape == 1 ? 0 : rng() % u;
        int w = rng() % 100;
        g[u].emplace_back(u, p, w);
        g[p].emplace_back(p, u, w);
        edges.emplace_back(u, p);
        weight[u][p] = w;
        weight[p][u] = w;
      }
      DynamicDiameter<long long> diameter(g);
      for (int step = 0; step < 100; ++step) {
        if (n > 1) {
          auto [u, v] = edges[rng() % edges.size()];
          long long w = rng() % 100;
          weight[u][v] = w;
          weight[v][u] = w;
          diameter.update(u, v, w);
        }
        vector<vector<long long>> distance(n, vector<long long>(n));
        long long expected = 0;
        for (int s = 0; s < n; ++s) {
          auto dfs = [&](auto&& self, int u, int parent) -> void {
            expected = max(expected, distance[s][u]);
            for (auto e : g[u]) {
              if (e.to != parent) {
                distance[s][e.to] = distance[s][u] + weight[u][e.to];
                self(self, e.to, u);
              }
            }
          };
          dfs(dfs, s, -1);
        }
        auto [length, endpoints] = diameter.get();
        auto [u, v] = endpoints;
        // 重み0や同長の候補があっても、長さは全点対の最大距離になる。
        assert(length == expected);
        // 両端は補助頂点でなく元の頂点で、実際にその長さの経路を持つ。
        assert(0 <= u && u < n && 0 <= v && v < n);
        assert(distance[u][v] == expected);
      }
    }
  }
}
