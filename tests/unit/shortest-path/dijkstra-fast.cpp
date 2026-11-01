// Verify: shortest-path/dijkstra-fast.hpp
// Verify: graph/static-graph.hpp
// 静的グラフの隣接辺を直接確認し、最短距離・親の復元を全単純路のDFSと比較する。
#include <bits/stdc++.h>
using namespace std;
#include "shortest-path/dijkstra-fast.hpp"

using Graph = vector<vector<pair<int, long long>>>;

vector<long long> enumerate_paths(const Graph& g, int source) {
  const long long inf = 1LL << 60;
  vector<long long> distance(g.size(), inf);
  auto dfs = [&](auto&& self, int u, unsigned visited, long long cost) -> void {
    distance[u] = min(distance[u], cost);
    for (auto [v, weight] : g[u]) {
      if (!(visited >> v & 1)) {
        self(self, v, visited | (1U << v), cost + weight);
      }
    }
  };
  dfs(dfs, source, 1U << source, 0);
  for (auto& x : distance) {
    if (x == inf) {
      x = -1;
    }
  }
  return distance;
}

void check_path(const Graph& graph, const vector<long long>& distance, int source, int goal,
                const vector<int>& path) {
  // 復元した列の両端は指定した始点・終点で、頂点を重複しない単純路になる。
  assert(!path.empty() && path.front() == source && path.back() == goal);
  assert(set<int>(path.begin(), path.end()).size() == path.size());
  for (int i = 1; i < (int)path.size(); ++i) {
    int u = path[i - 1];
    int v = path[i];
    bool found = false;
    for (auto [to, weight] : graph[u]) {
      if (to == v && distance[u] + weight == distance[v]) {
        found = true;
      }
    }
    // 各遷移が実在する辺で、最短距離の差に等しい重みを持つことを確認する。
    assert(found);
  }
}

int main() {
  mt19937 rng(802);
  for (int n = 1; n <= 7; ++n) {
    for (int trial = 0; trial < 100; ++trial) {
      Graph reference(n);
      int edges = trial == 0 ? 0 : rng() % (n * n + 1);
      StaticGraph<long long> graph(n, edges);
      for (int i = 0; i < edges; ++i) {
        int u = rng() % n;
        int v = rng() % n;
        long long weight = rng() % 30;
        reference[u].emplace_back(v, weight);
        graph.add_edge(u, v, weight);
      }
      for (int u = 0; u < n; ++u) {
        vector<pair<int, long long>> got;
        for (auto [v, weight] : graph[u]) {
          got.emplace_back(v, weight);
        }
        sort(got.begin(), got.end());
        auto expected = reference[u];
        sort(expected.begin(), expected.end());
        // 圧縮された隣接配列に、各頂点の辺が多重度と重みを含めて保存されている。
        assert(got == expected);
      }
      for (int source = 0; source < n; ++source) {
        auto expected = enumerate_paths(reference, source);

        // 静的隣接配列版の全距離と、全単純路の最短値が一致する。
        assert(dijkstra(graph, source) == expected);
        for (int goal = 0; goal < n; ++goal) {
          // 一点の到達時に打ち切るAPIも、到達不能を含めて同じ距離を返す。
          assert(dijkstra_point(graph, source, goal) == expected[goal]);
        }

        auto got = dijkstra_restore(graph, source);
        for (int goal = 0; goal < n; ++goal) {
          // decrease-keyや到達不能の扱いを、全単純路の列挙結果と照合する。
          assert(got[goal].first == expected[goal]);
          if (expected[goal] == -1) {
            continue;
          }
          vector<int> path;
          int v = goal;
          for (int count = 0; count <= n && v != -1; ++count) {
            path.push_back(v);
            v = got[v].second;
          }
          reverse(path.begin(), path.end());
          check_path(reference, expected, source, goal, path);
        }
      }
    }
  }
}
