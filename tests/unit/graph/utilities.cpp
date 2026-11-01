// Verify: graph/graph-utility.hpp
// int/pairの隣接リストで、木の全点対距離・直径・復元経路をBFSと比較する。
#include <bits/stdc++.h>
using namespace std;
#include "graph/graph-utility.hpp"

int main() {
  mt19937 rng(907);
  for (int n = 1; n <= 40; ++n) {
    vector<vector<int>> g(n);
    vector<vector<pair<int, long long>>> wg(n);
    for (int u = 1; u < n; ++u) {
      int p = rng() % u;
      int w = 1 + rng() % 100;
      g[u].push_back(p);
      g[p].push_back(u);
      wg[u].emplace_back(p, w);
      wg[p].emplace_back(u, w);
    }
    long long diameter = 0;
    int unit_diameter = 0;
    for (int s = 0; s < n; ++s) {
      vector<int> parent(n, -1);
      vector<int> dist(n, -1);
      vector<long long> weighted_dist(n);
      vector<int> q{s};
      dist[s] = 0;
      for (int i = 0; i < (int)q.size(); ++i) {
        for (auto [to, cost] : wg[q[i]]) {
          if (dist[to] != -1) {
            continue;
          }
          parent[to] = q[i];
          dist[to] = dist[q[i]] + 1;
          weighted_dist[to] = weighted_dist[q[i]] + cost;
          q.push_back(to);
        }
      }
      // 単位辺のBFS距離と、同じ経路の重みを足した距離を比較する。
      assert(Depth(g, s) == dist);
      assert(Depth(wg, s) == weighted_dist);
      for (int t = 0; t < n; ++t) {
        vector<int> path;
        for (int u = t; u != -1; u = parent[u]) {
          path.push_back(u);
        }
        reverse(path.begin(), path.end());
        // 木の唯一の経路が、親を1つずつたどった列と一致する。
        assert(Path(g, s, t) == path && Path(wg, s, t) == path);
        diameter = max(diameter, weighted_dist[t]);
        unit_diameter = max(unit_diameter, dist[t]);
      }
    }
    auto d = Diameter(g);
    auto wd = Diameter(wg);
    // 直径の長さと両端を、全点対の最大距離で照合する。
    assert(d.second == unit_diameter && Depth(g, d.first.first)[d.first.second] == d.second);
    assert(wd.second == diameter && Depth(wg, wd.first.first)[wd.first.second] == wd.second);
  }
}
