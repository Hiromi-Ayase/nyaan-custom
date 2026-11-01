// Verify: shortest-path/dijkstra-abstruct.hpp
// 文字列を頂点名にしてコールバックで辺を生成し、一点・複数終点・全到達状態を全単純路と比較する。
#include <bits/stdc++.h>
using namespace std;
#include "shortest-path/dijkstra-abstruct.hpp"

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
  mt19937 rng(803);
  for (int n = 1; n <= 7; ++n) {
    for (int trial = 0; trial < 60; ++trial) {
      Graph graph(n);
      vector<string> names(n);
      map<string, int> ids;
      for (int i = 0; i < n; ++i) {
        names[i] = "vertex_" + to_string(i * 17 + 3);
        ids[names[i]] = i;
      }
      for (int i = 0; i < n * n / 2; ++i) {
        int u = rng() % n;
        graph[u].emplace_back(rng() % n, rng() % 10);
      }
      function<void(string, long long, function<void(string, long long)>)> transition =
          [&](string from, long long cost, auto push) {
            for (auto [v, weight] : graph[ids[from]]) {
              push(names[v], cost + weight);
            }
          };
      int source = rng() % n;
      auto expected = enumerate_paths(graph, source);
      for (int goal = 0; goal < n; ++goal) {
        auto result = dijkstra_abstruct<string, long long>(transition, names[source], names[goal]);
        // 数値添字以外の状態でも、全探索と到達可能性が一致する。
        assert(result.reachable == (expected[goal] != -1));
        if (result.reachable) {
          // 返された最短距離が、全ての単純路の最小値と一致する。
          assert(result.dist == expected[goal]);
          vector<int> path;
          for (const auto& name : result.path) {
            path.push_back(ids.at(name));
          }
          check_path(graph, expected, source, goal, path);
        }
      }
      function<bool(string)> is_goal = [&](string v) { return ids[v] % 2 == 0; };
      long long best = LLONG_MAX;
      for (int i = 0; i < n; i += 2) {
        if (expected[i] != -1) {
          best = min(best, expected[i]);
        }
      }
      auto nearest = dijkstra_abstruct<string, long long>(transition, names[source], is_goal);
      // 複数終点では、到達できる候補の中で最も近い頂点で探索を終える。
      assert(nearest.reachable == (best != LLONG_MAX));
      if (nearest.reachable) {
        assert(is_goal(nearest.goal) && nearest.dist == best);
      }
      auto all = dijkstra_abstruct<string, long long, false>(transition, names[source]);
      for (int i = 0; i < n; ++i) {
        // 終点を指定しない探索のmapは、到達可能な全状態とその距離を保持する。
        assert(all.mp.count(names[i]) == (expected[i] != -1));
        if (expected[i] != -1) {
          assert(all.mp.at(names[i]).first == expected[i]);
        }
      }
    }
  }
}
