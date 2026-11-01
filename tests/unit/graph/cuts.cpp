// Verify: graph/lowlink.hpp
// Verify: graph/two-edge-connected-components.hpp
// Verify: graph/biconnected-components.hpp
// 辺・頂点を削除したBFSで橋と関節点を求め、全単純閉路から二重頂点連結成分を作る。
#include <bits/stdc++.h>
using namespace std;
#include "graph/lowlink.hpp"
#include "graph/two-edge-connected-components.hpp"
#include "graph/biconnected-components.hpp"

vector<int> components(int n, const vector<pair<int, int>>& edges, int removed_vertex,
                       const set<int>& removed_edges) {
  vector<int> label(n, -1);
  for (int s = 0; s < n; ++s) {
    if (s == removed_vertex || label[s] != -1) {
      continue;
    }
    vector<int> q{s};
    label[s] = s;
    for (int i = 0; i < (int)q.size(); ++i) {
      for (int e = 0; e < (int)edges.size(); ++e) {
        if (removed_edges.count(e)) {
          continue;
        }
        auto [u, v] = edges[e];
        if (v == q[i]) {
          swap(u, v);
        }
        if (u != q[i] || v == removed_vertex || label[v] != -1) {
          continue;
        }
        label[v] = s;
        q.push_back(v);
      }
    }
  }
  return label;
}

int count_components(const vector<int>& labels) {
  set<int> distinct(labels.begin(), labels.end());
  distinct.erase(-1);
  return distinct.size();
}

int main() {
  mt19937 rng(902);
  for (int n = 1; n <= 8; ++n) {
    for (int trial = 0; trial < 100; ++trial) {
      vector<pair<int, int>> edges;
      vector<vector<int>> g(n);
      for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
          if (rng() % 3 == 0) {
            edges.emplace_back(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
          }
        }
      }
      int base = count_components(components(n, edges, -1, {}));
      set<int> bridge_ids;
      set<pair<int, int>> bridges;
      set<int> articulation;
      for (int e = 0; e < (int)edges.size(); ++e) {
        if (count_components(components(n, edges, -1, {e})) > base) {
          bridge_ids.insert(e);
          bridges.insert(edges[e]);
        }
      }
      for (int v = 0; v < n; ++v) {
        if (count_components(components(n, edges, v, {})) > base) {
          articulation.insert(v);
        }
      }
      vector<vector<pair<int, long long>>> weighted(n);
      for (int u = 0; u < n; ++u) {
        for (int v : g[u]) {
          weighted[u].emplace_back(v, (long long)u * 1000000000 + v);
        }
      }
      LowLink weighted_low(weighted);
      // 重み付きpairでも、橋と関節点は同じ削除BFSの期待値に一致する。
      assert(set(weighted_low.bridge.begin(), weighted_low.bridge.end()) == bridges);
      assert(set(weighted_low.articulation.begin(), weighted_low.articulation.end()) ==
             articulation);
      LowLink low(g);
      // 橋・関節点は、実際に削除したとき連結成分数を増やす辺・頂点に一致する。
      assert(set(low.bridge.begin(), low.bridge.end()) == bridges);
      assert(set(low.articulation.begin(), low.articulation.end()) == articulation);
      TwoEdgeConnectedComponents two(g);
      TwoEdgeConnectedComponents weighted_two(weighted);
      auto labels = components(n, edges, -1, bridge_ids);
      for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
          // 橋を全て取り除いたグラフの連結成分と一致する。
          assert((two[u] == two[v]) == (labels[u] == labels[v]));
          assert((weighted_two[u] == weighted_two[v]) == (labels[u] == labels[v]));
        }
      }
      // 辺同士が同一の単純閉路に現れたら同じブロックとし、その推移閉包を取る。
      int m = edges.size();
      vector<int> block(m);
      iota(block.begin(), block.end(), 0);
      for (int s = 0; s < n; ++s) {
        vector<int> path;
        auto dfs = [&](auto&& self, int u, unsigned visited) -> void {
          for (int e = 0; e < m; ++e) {
            auto [a, b] = edges[e];
            if (b == u) {
              swap(a, b);
            }
            if (a != u) {
              continue;
            }
            if (b == s && path.size() >= 2) {
              int old = block[e];
              for (int id : path) {
                int target = block[id];
                for (int& x : block) {
                  if (x == target) {
                    x = old;
                  }
                }
              }
            } else if (!(visited >> b & 1)) {
              path.push_back(e);
              self(self, b, visited | (1U << b));
              path.pop_back();
            }
          }
        };
        dfs(dfs, s, 1U << s);
      }
      map<int, set<pair<int, int>>> expected_map;
      for (int e = 0; e < m; ++e) {
        expected_map[block[e]].insert(edges[e]);
      }
      set<set<pair<int, int>>> expected;
      for (auto& [id, es] : expected_map) {
        expected.insert(es);
      }
      BiConnectedComponents bi(g);
      set<set<pair<int, int>>> actual;
      for (auto& es : bi.bc) {
        actual.emplace(es.begin(), es.end());
      }
      // 全閉路から得たブロック分割と一致し、橋も1辺のブロックとして残る。
      assert(actual == expected);
      BiConnectedComponents weighted_bi(weighted);
      set<set<pair<int, int>>> weighted_blocks;
      for (const auto& block : weighted_bi.bc) {
        weighted_blocks.emplace(block.begin(), block.end());
      }
      // pair隣接リストからの二重頂点連結成分も、全閉路列挙と照合する。
      assert(weighted_blocks == expected);
      if (!edges.empty()) {
        // 並行する2辺はどちらも橋でない。LowLinkの多重辺対応を別に確認する。
        auto [u, v] = edges[0];
        g[u].push_back(v);
        g[v].push_back(u);
        LowLink parallel(g);
        bridges.erase(edges[0]);
        assert(set(parallel.bridge.begin(), parallel.bridge.end()) == bridges);
      }
    }
  }
}
