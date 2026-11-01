// Verify: shortest-path/bellman-ford.hpp
// Verify: shortest-path/warshall-floyd.hpp
// Verify: shortest-path/dual-of-shortest-path.hpp
// ポテンシャルで負閉路のない負辺グラフを作り、全単純路と比較する。別に負閉路の影響範囲も確認する。
#include <bits/stdc++.h>
using namespace std;
#include "shortest-path/bellman-ford.hpp"
#include "shortest-path/warshall-floyd.hpp"
#include "shortest-path/dual-of-shortest-path.hpp"

int main() {
  mt19937 rng(804);
  const long long inf = LLONG_MAX / 2;
  for (int n = 1; n <= 7; ++n) {
    for (int trial = 0; trial < 70; ++trial) {
      vector<int> potential(n);
      for (auto& x : potential) {
        x = int(rng() % 21) - 10;
      }
      vector<vector<pair<int, long long>>> graph(n);
      Edges<long long> edges;
      Dual_of_Shortest_Path<long long> dual(n);
      vector<vector<long long>> matrix(n, vector<long long>(n, inf));
      for (int i = 0; i < n * n / 2 + n; ++i) {
        // 各頂点から次の頂点への辺を加え、全点到達可能にしてINFと負辺の加算を避ける。
        int u = i < n ? i : rng() % n;
        int v = i < n ? (i + 1) % n : rng() % n;
        long long weight = rng() % 10 + potential[v] - potential[u];
        graph[u].emplace_back(v, weight);
        edges.emplace_back(u, v, weight);
        dual.add_edge(u, v, weight);
        matrix[u][v] = min(matrix[u][v], weight);
      }
      auto floyd = matrix;
      warshall_floyd(floyd);
      for (int source = 0; source < n; ++source) {
        vector<long long> expected(n, inf);
        auto dfs = [&](auto&& self, int u, unsigned visited, long long cost) -> void {
          expected[u] = min(expected[u], cost);
          for (auto [v, weight] : graph[u]) {
            if (!(visited >> v & 1)) {
              self(self, v, visited | (1U << v), cost + weight);
            }
          }
        };
        dfs(dfs, source, 1U << source, 0);
        // 負閉路がないので最短単純路が存在し、負辺を含むBellman-Fordと全探索が一致する。
        assert(bellman_ford(n, edges, source) == expected);
        // 全点到達可能な入力では、Warshall-Floydの各行も同じ全探索に一致する。
        assert(floyd[source] == expected);
        // 差分制約の始点指定版は、各頂点の値との差の最大値として最短距離を返す。
        assert(dual.solve(source) == expected);
      }
      auto feasible = dual.solve();
      // 作ったポテンシャルが実行可能解なので、制約系は必ず可解である。
      assert((int)feasible.size() == n);
      for (auto e : edges) {
        // 返された値が、登録した全ての差分不等式を直接満たす。
        assert(feasible[e.to] <= feasible[e.src] + e.cost);
      }
      dual.add_edge(0, 0, -1);
      // 自分自身より1小さいという制約を加えると、矛盾した系として空列を返す。
      assert(dual.solve().empty());
    }
  }
  Edges<long long> edges{{0, 1, 2}, {1, 2, -2}, {2, 1, 1}, {0, 3, 5}, {4, 4, -1}};
  // 始点から到達する負閉路は検出される。
  assert(bellman_ford(5, edges, 0).empty());
  // 終点1は負閉路の影響を受けるので、終点指定でも解なしになる。
  assert(bellman_ford(5, edges, 0, 1).empty());
  auto safe_goal = bellman_ford(5, edges, 0, 3);
  // 負閉路から到達できない終点3の最短距離は有限のまま求められる。
  assert(!safe_goal.empty() && safe_goal[3] == 5);
  auto isolated = bellman_ford(5, edges, 3);
  // 到達不能な別成分に負閉路があっても、始点3の探索には影響しない。
  assert(isolated == vector<long long>({inf, inf, inf, 0, inf}));
  vector<vector<long long>> empty;
  warshall_floyd(empty);
  // 空の距離行列はそのまま処理できる。
  assert(empty.empty());
}
