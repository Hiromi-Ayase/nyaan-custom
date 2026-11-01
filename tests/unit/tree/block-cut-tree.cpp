// Verify: tree/block-cut-tree.hpp
// 頂点を削除した連結性と、Block Cut Tree上の関節点を通る経路の有無を比較する。
#include <bits/stdc++.h>
using namespace std;
#include "tree/block-cut-tree.hpp"

vector<bool> reach(const vector<vector<int>>& g, int source, int removed) {
  vector<bool> seen(g.size());
  if (source == removed) {
    return seen;
  }
  vector<int> q{source};
  seen[source] = true;
  for (int i = 0; i < (int)q.size(); ++i) {
    for (int v : g[q[i]]) {
      if (v != removed && !seen[v]) {
        seen[v] = true;
        q.push_back(v);
      }
    }
  }
  return seen;
}

int main() {
  mt19937 rng(1008);
  for (int n = 2; n <= 10; ++n) {
    for (int trial = 0; trial < 100; ++trial) {
      vector<set<int>> edges(n);
      for (int u = 1; u < n; ++u) {
        int p = rng() % u;
        edges[u].insert(p);
        edges[p].insert(u);
      }
      for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
          if (rng() % 5 == 0) {
            edges[u].insert(v);
            edges[v].insert(u);
          }
        }
      }
      vector<vector<int>> g(n);
      for (int u = 0; u < n; ++u) {
        g[u] = vector<int>(edges[u].begin(), edges[u].end());
      }
      BlockCutTree bct(g);
      int total_edges = 0;
      for (auto& list : bct.aux) {
        total_edges += list.size();
      }
      // 連結グラフのBlock Cut Treeは連結で、辺数が頂点数-1になる。
      assert(total_edges == 2 * (bct.size() - 1));
      assert(reach(bct.aux, 0, -1) == vector<bool>(bct.size(), true));
      int articulation_count = 0;
      for (int removed = 0; removed < n; ++removed) {
        auto connected = reach(g, removed == 0 ? 1 : 0, removed);
        bool articulation = count(connected.begin(), connected.end(), true) != n - 1;
        articulation_count += articulation;
        // 関節点かどうかを、削除後の成分数で判定した値と比較する。
        assert(bct.is_arti(removed) == articulation);
        if (!articulation) {
          continue;
        }
        for (int u = 0; u < n; ++u) {
          if (u == removed) {
            continue;
          }
          auto original = reach(g, u, removed);
          auto compressed = reach(bct.aux, bct.id(u), bct.id(removed));
          for (int v = 0; v < n; ++v) {
            if (v != removed) {
              // 元の関節点を除いて分断される頂点対は、補助木の対応頂点を除いても分断される。
              assert(original[v] == compressed[bct.id(v)]);
            }
          }
        }
      }
      assert(bct.arti() == articulation_count);
    }
  }
}
