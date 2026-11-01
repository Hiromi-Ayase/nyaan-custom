// Verify: graph/functional-graph.hpp
// Verify: graph/namori.hpp
// 辺を繰り返したどって閉路を求め、木へ変換しても頂点・辺・重みが保存されることを検証する。
#include <bits/stdc++.h>
using namespace std;
#include "graph/functional-graph.hpp"
#include "graph/namori.hpp"

int main() {
  mt19937 rng(905);
  for (int n = 1; n <= 50; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      vector<int> to(n);
      vector<int> weights(n);
      for (int u = 0; u < n; ++u) {
        to[u] = rng() % n;
        weights[u] = (int)(rng() % 21) - 10;
      }
      FunctionalGraph<int> f(n, to, weights);
      FunctionalGraph<int> unit(n, to);
      vector<set<int>> cycle(n);
      set<set<int>> expected;
      for (int s = 0; s < n; ++s) {
        vector<int> path;
        int u = s;
        while (find(path.begin(), path.end(), u) == path.end()) {
          path.push_back(u);
          u = to[u];
        }
        cycle[s] = set<int>(find(path.begin(), path.end(), u), path.end());
        expected.insert(cycle[s]);
        // 行き先・重みと、重み省略時の1が保たれる。
        assert(f.to[s] == to[s] && f.weight[s] == weights[s]);
        assert(unit.weight[s] == 1);
      }
      set<set<int>> actual;
      for (auto& loop : f.get_loops()) {
        actual.emplace(loop.begin(), loop.end());
      }
      // 閉路頂点の集合は、各頂点から繰り返したどった結果と一致する。
      assert(actual == expected);
      for (auto& loop : f.get_loops_with_weight()) {
        for (int i = 0; i < (int)loop.size(); ++i) {
          auto [u, w] = loop[i];
          // 閉路列の次の頂点と辺重みも元の有向辺と一致する。
          assert(to[u] == loop[(i + 1) % loop.size()].first && weights[u] == w);
        }
      }
      vector<int> visits(n + 1);
      auto dfs = [&](auto&& self, int u, int representative) -> void {
        ++visits[u];
        // 仮想根からの木に循環や頂点の重複がない。
        assert(visits[u] == 1);
        for (auto e : f.g[u]) {
          int r = u == n ? e.to : representative;
          // 同じ木の代表は仮想根の直下にあり、元の閉路に属する。
          assert(f.represent[e.to] == r && cycle[e.to].count(r));
          if (u != n) {
            assert(to[e.to] == u && e.cost == weights[e.to]);
          }
          self(self, e.to, r);
        }
      };
      dfs(dfs, n, -1);
      // 全ての元頂点が仮想根の木に1度ずつ現れる。
      assert(visits == vector<int>(n + 1, 1));
    }
    // 既知の閉路に枝を足したなもり。長さ1・2の閉路も対象にする。
    for (int k = 1; k <= n; ++k) {
      Namori<int> namori(n);
      vector<tuple<int, int, int>> edges;
      vector<int> root_of(n);
      for (int u = 0; u < k; ++u) {
        edges.emplace_back(u, (u + 1) % k, 1 + u);
        root_of[u] = u;
      }
      for (int u = k; u < n; ++u) {
        int p = rng() % u;
        edges.emplace_back(u, p, 1 + u);
        root_of[u] = root_of[p];
      }
      shuffle(edges.begin(), edges.end(), rng);
      for (auto [u, v, w] : edges) {
        namori.add_edge(u, v, w);
      }
      // 閉路長と、各頂点が属する枝の根が生成時の値と一致する。
      assert((int)namori.loop.size() == k);
      set<pair<int, int>> mapped;
      for (int u = 0; u < n; ++u) {
        assert(namori.root(u) == root_of[u]);
        mapped.insert(namori.idx(u));
      }
      // 部分木内の番号への写像は単射で、全頂点を保存する。
      assert((int)mapped.size() == n);
      multiset<tuple<int, int, int>> expected_edges;
      multiset<tuple<int, int, int>> restored;
      for (auto [u, v, w] : edges) {
        expected_edges.emplace(min(u, v), max(u, v), w);
      }
      for (int i = 0; i < k; ++i) {
        int u = namori.loop[i].first;
        int v = namori.loop[(i + 1) % k].first;
        restored.emplace(min(u, v), max(u, v), namori.loop[i].second);
        vector<int> inverse(namori.aux[i].size());
        for (int x = 0; x < n; ++x) {
          if (namori.idx(x).first == i) {
            inverse[namori.idx(x).second] = x;
          }
        }
        for (int a = 0; a < (int)inverse.size(); ++a) {
          for (auto e : namori.aux[i][a]) {
            int x = inverse[a];
            int y = inverse[e.to];
            restored.emplace(min(x, y), max(x, y), e.cost);
          }
        }
      }
      // 閉路と枝を合わせ直すと、入力の全辺が重み・多重度込みで復元される。
      assert(restored == expected_edges);
      if (k >= 3) {
        WeightedGraph<int> undirected(n);
        for (auto [u, v, w] : edges) {
          undirected[u].emplace_back(u, v, w);
          undirected[v].emplace_back(v, u, w);
        }
        FunctionalGraph<int> f(n, undirected);
        auto loops = f.get_loops();
        set<int> expected_loop;
        for (int u = 0; u < k; ++u) {
          expected_loop.insert(u);
        }
        // 無向単純グラフから構築するAPIも、生成時の閉路を取り出す。
        assert(loops.size() == 1 && set<int>(loops[0].begin(), loops[0].end()) == expected_loop);
      }
    }
  }
}
