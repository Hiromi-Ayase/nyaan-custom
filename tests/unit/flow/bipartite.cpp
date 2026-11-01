// Verify: flow/flow-on-bipartite-graph.hpp
// 全ての頂点被覆とマッチングを列挙し、最大マッチング・独立集合・最小被覆の値と復元を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "flow/flow-on-bipartite-graph.hpp"

int main() {
  mt19937 rng(1102);
  for (int left = 0; left <= 5; ++left) {
    for (int right = 0; right <= 5; ++right) {
      for (int trial = 0; trial < 80; ++trial) {
        BipartiteGraph g(left, right);
        vector<pair<int, int>> edges;
        for (int u = 0; u < left; ++u) {
          for (int v = 0; v < right; ++v) {
            if (rng() % 4 == 0) {
              edges.emplace_back(u, v);
              g.add_edge(u, v);
            }
          }
        }
        auto brute = [&](auto&& self, int u, unsigned used) -> int {
          if (u == left) {
            return 0;
          }
          int best = self(self, u + 1, used);
          for (auto [a, b] : edges) {
            if (a == u && !(used >> b & 1)) {
              best = max(best, 1 + self(self, u + 1, used | (1U << b)));
            }
          }
          return best;
        };
        int matching_size = brute(brute, 0, 0);
        // 左頂点ごとに未使用の右頂点を選ぶ全探索と最大流の値が一致する。
        if (trial % 2 == 0) {
          assert(g.flow() == matching_size);
        }
        auto matching = g.MaximumMatching();
        assert((int)matching.size() == matching_size);
        set<int> used_left;
        set<int> used_right;
        for (auto [u, v] : matching) {
          // マッチングは実在する辺だけで構成され、両側の端点を重複しない。
          assert(find(edges.begin(), edges.end(), make_pair(u, v)) != edges.end());
          assert(used_left.insert(u).second && used_right.insert(v).second);
        }
        int cover_size = left + right;
        for (unsigned mask = 0; mask < (1U << (left + right)); ++mask) {
          bool covers = true;
          for (auto [u, v] : edges) {
            if (!(mask >> u & 1) && !(mask >> (left + v) & 1)) {
              covers = false;
            }
          }
          if (covers) {
            cover_size = min(cover_size, __builtin_popcount(mask));
          }
        }
        auto [cl, cr] = g.MinimumVertexCover();
        auto [il, ir] = g.MaximumIndependentSet();
        set<int> cover_left(cl.begin(), cl.end());
        set<int> cover_right(cr.begin(), cr.end());
        set<int> independent_left(il.begin(), il.end());
        set<int> independent_right(ir.begin(), ir.end());
        // 全頂点部分集合から求めた最小被覆サイズと、補集合である最大独立集合サイズを比較する。
        assert((int)(cl.size() + cr.size()) == cover_size);
        assert((int)(il.size() + ir.size()) == left + right - cover_size);
        for (auto [u, v] : edges) {
          assert(cover_left.count(u) || cover_right.count(v));
          assert(!(independent_left.count(u) && independent_right.count(v)));
        }
        vector<int> degree(left + right);
        for (auto [u, v] : edges) {
          ++degree[u];
          ++degree[left + v];
        }
        if (find(degree.begin(), degree.end(), 0) == degree.end()) {
          auto edge_cover = g.MinimumEdgeCover();
          vector<bool> covered(left + right);
          for (auto [u, v] : edge_cover) {
            assert(find(edges.begin(), edges.end(), make_pair(u, v)) != edges.end());
            covered[u] = true;
            covered[left + v] = true;
          }
          // 孤立点がなければ全頂点を覆い、最小辺被覆のサイズV-最大マッチングを達成する。
          assert(covered == vector<bool>(left + right, true));
          assert((int)edge_cover.size() == left + right - matching_size);
        }
      }
    }
  }
}
