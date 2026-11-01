// Verify: shortest-path/dijkstra.hpp
// Verify: shortest-path/dijkstra-radix-heap.hpp
// Verify: shortest-path/dijkstra-with-restore.hpp
// Verify: shortest-path/bfs01.hpp
// Verify: shortest-path/bfs-restore.hpp
// Verify: shortest-path/restore-shortest-path.hpp
// 全単純路のDFSを期待値とし、到達不能・0辺・多重辺・自己ループと復元された頂点列を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "shortest-path/dijkstra.hpp"
#include "shortest-path/dijkstra-radix-heap.hpp"
#include "shortest-path/dijkstra-with-restore.hpp"
#include "shortest-path/bfs01.hpp"
#include "shortest-path/bfs-restore.hpp"
#include "shortest-path/restore-shortest-path.hpp"

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
  mt19937 rng(801);
  for (int n = 1; n <= 7; ++n) {
    for (int trial = 0; trial < 60; ++trial) {
      Graph reference(n);
      WeightedGraph<long long> graph(n);
      for (int i = 0; i < n * n / 2; ++i) {
        int u = rng() % n;
        int v = rng() % n;
        long long weight = trial % 3 == 0 ? 1 : trial % 3 == 1 ? rng() % 2 : rng() % 30;
        reference[u].emplace_back(v, weight);
        graph[u].emplace_back(u, v, weight);
      }
      for (int source = 0; source < n; ++source) {
        auto expected = enumerate_paths(reference, source);
        // 非負重みでは最短の単純路が存在するので、DFSの全列挙とDijkstraを比較できる。
        assert(dijkstra(graph, source) == expected);
        // RadixHeapを使う版でも、0辺や同距離の候補を含めて距離が一致する。
        assert(dijkstra_radix_heap(graph, source) == expected);
        if (trial % 3 <= 1) {
          // 0/1重み専用のdeque版も、同じ全探索の距離と一致する。
          assert(bfs01(graph, source) == expected);
        }
        auto restored = dijkstra_restore(graph, source);
        for (int goal = 0; goal < n; ++goal) {
          // 復元付きAPIの距離も一致し、到達不能なら親も-1になる。
          assert(restored[goal].first == expected[goal]);
          if (expected[goal] == -1) {
            assert(restored[goal].second == -1);
            continue;
          }
          vector<int> path;
          int v = goal;
          for (int count = 0; count <= n && v != -1; ++count) {
            path.push_back(v);
            v = restored[v].second;
          }
          reverse(path.begin(), path.end());
          check_path(reference, expected, source, goal, path);
          if (trial % 3 == 0 && source != goal) {
            // 距離配列だけから復元するAPIは、正の辺と異なる両端という前提で試す。
            check_path(reference, expected, source, goal,
                       restore_shortest_path(graph, expected, source, goal));
          }
        }
        if (trial % 3 == 0) {
          vector<vector<int>> unweighted(n);
          for (int u = 0; u < n; ++u) {
            for (auto [v, weight] : reference[u]) {
              unweighted[u].push_back(v);
            }
          }
          auto bfs = bfs_restore(unweighted, source);
          for (int v = 0; v < n; ++v) {
            // 全辺の重みが1のとき、通常のBFSでも同じ最小辺数が得られる。
            assert(bfs[v].first == expected[v]);
            if (v != source && expected[v] != -1) {
              int parent = bfs[v].second;
              // BFSの親は実在する直前の頂点で、距離がちょうど1小さい。
              assert(0 <= parent && parent < n && expected[parent] + 1 == expected[v]);
              assert(find(unweighted[parent].begin(), unweighted[parent].end(), v) !=
                     unweighted[parent].end());
            }
          }
        }
      }
    }
  }
}
