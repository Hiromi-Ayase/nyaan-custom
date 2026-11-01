// Verify: graph/graph-template.hpp
// Verify: graph/graph-utility.hpp
// 入力の0/1始まり・有向/無向を確認し、木の全点対距離と復元経路をBFSで比較する。
#include <bits/stdc++.h>
using namespace std;
#include "graph/graph-template.hpp"
#include "graph/graph-utility.hpp"

int main() {
  for (bool one : {false, true}) {
    for (bool directed : {false, true}) {
      for (bool weighted : {false, true}) {
        vector<tuple<int, int, int>> edges{{0, 1, 3}, {1, 2, 5}, {2, 0, 7}, {2, 2, 11}};
        ostringstream output;
        for (auto [u, v, w] : edges) {
          output << u + one << ' ' << v + one;
          if (weighted) {
            output << ' ' << w;
          }
          output << '\n';
        }
        auto input = output.str();
        istringstream stream(input);
        auto* old = cin.rdbuf(stream.rdbuf());
        if (weighted) {
          auto g = wgraph<int>(3, 4, directed, one);
          vector<vector<pair<int, int>>> expected(3);
          for (auto [u, v, w] : edges) {
            expected[u].emplace_back(v, w);
            if (!directed) {
              expected[v].emplace_back(u, w);
            }
          }
          for (int u = 0; u < 3; ++u) {
            vector<pair<int, int>> actual;
            for (auto e : g[u]) {
              // 辺に保持されるsrcも入力元頂点と一致する。
              assert(e.src == u);
              actual.emplace_back(e.to, e.cost);
            }
            // 隣接リストの順序・重み・自己ループの多重度が入力規約どおりになる。
            assert(actual == expected[u]);
          }
        } else {
          auto g = graph(3, 4, directed, one);
          vector<vector<int>> expected(3);
          for (auto [u, v, w] : edges) {
            expected[u].push_back(v);
            if (!directed) {
              expected[v].push_back(u);
            }
          }
          // 重みなし入力も指定した添字と向きで読み込める。
          assert(g == expected);
        }
        cin.rdbuf(old);
        stream = istringstream(input);
        cin.rdbuf(stream.rdbuf());
        auto es = esgraph<int>(3, 4, weighted, one);
        cin.rdbuf(old);
        for (int i = 0; i < 4; ++i) {
          auto [u, v, w] = edges[i];
          // 辺列形式では逆辺を補わず、重み省略時は1になる。
          assert(es[i].src == u && es[i].to == v && es[i].cost == (weighted ? w : 1));
        }
        stream = istringstream(input);
        cin.rdbuf(stream.rdbuf());
        auto matrix = adjgraph(3, 4, 999, weighted, directed, one);
        cin.rdbuf(old);
        vector<vector<int>> expected(3, vector<int>(3, 999));
        for (auto [u, v, w] : edges) {
          expected[u][v] = weighted ? w : 1;
          if (!directed) {
            expected[v][u] = weighted ? w : 1;
          }
        }
        // 存在しない辺は指定したINFのままで、行列の向きと重みが一致する。
        assert(matrix == expected);
      }
    }
  }
  mt19937 rng(907);
  for (int n = 1; n <= 40; ++n) {
    UnweightedGraph g(n);
    WeightedGraph<long long> wg(n);
    for (int u = 1; u < n; ++u) {
      int p = rng() % u;
      int w = 1 + rng() % 100;
      g[u].push_back(p);
      g[p].push_back(u);
      wg[u].emplace_back(u, p, w);
      wg[p].emplace_back(p, u, w);
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
        for (auto e : wg[q[i]]) {
          if (dist[e.to] != -1) {
            continue;
          }
          parent[e.to] = q[i];
          dist[e.to] = dist[q[i]] + 1;
          weighted_dist[e.to] = weighted_dist[q[i]] + e.cost;
          q.push_back(e.to);
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
