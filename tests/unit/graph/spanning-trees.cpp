// Verify: graph/kruskal.hpp
// Verify: graph/minimum-cost-arborescence.hpp
// 辺部分集合を全列挙し、連結性と入次数を直接調べて最小全域森・最小全域有向木を求める。
#include <bits/stdc++.h>
using namespace std;
#include "graph/kruskal.hpp"
#include "graph/minimum-cost-arborescence.hpp"

vector<bool> reach(int n, const Edges<long long>& es, unsigned mask, int s, bool directed) {
  vector<bool> seen(n);
  seen[s] = true;
  vector<int> q{s};
  for (int i = 0; i < (int)q.size(); ++i) {
    for (int e = 0; e < (int)es.size(); ++e) {
      if (!(mask >> e & 1)) {
        continue;
      }
      int u = es[e].src;
      int v = es[e].to;
      if (!directed && v == q[i]) {
        swap(u, v);
      }
      if (u == q[i] && !seen[v]) {
        seen[v] = true;
        q.push_back(v);
      }
    }
  }
  return seen;
}

int main() {
  mt19937 rng(904);
  for (int n = 1; n <= 6; ++n) {
    for (int trial = 0; trial < 120; ++trial) {
      Edges<long long> edges;
      int m = rng() % 11;
      for (int e = 0; e < m; ++e) {
        edges.emplace_back(rng() % n, rng() % n, (int)(rng() % 31) - 15);
      }
      unsigned all = (1U << m) - 1;
      int components = 0;
      vector<bool> seen(n);
      for (int u = 0; u < n; ++u) {
        if (!seen[u]) {
          ++components;
          auto current = reach(n, edges, all, u, false);
          for (int v = 0; v < n; ++v) {
            seen[v] = seen[v] || current[v];
          }
        }
      }
      long long forest = LLONG_MAX;
      vector<long long> arborescence(n, LLONG_MAX);
      for (unsigned mask = 0; mask <= all; ++mask) {
        int count = __builtin_popcount(mask);
        if (count != n - components && count != n - 1) {
          continue;
        }
        long long cost = 0;
        vector<int> indegree(n);
        for (int e = 0; e < m; ++e) {
          if (mask >> e & 1) {
            cost += edges[e].cost;
            ++indegree[edges[e].to];
          }
        }
        if (count == n - components) {
          bool valid = true;
          for (int u = 0; u < n; ++u) {
            if (reach(n, edges, mask, u, false) != reach(n, edges, all, u, false)) {
              valid = false;
            }
          }
          if (valid) {
            forest = min(forest, cost);
          }
        }
        if (count == n - 1) {
          for (int root = 0; root < n; ++root) {
            bool valid = true;
            for (int v = 0; v < n; ++v) {
              if (indegree[v] != (v != root)) {
                valid = false;
              }
            }
            if (valid && reach(n, edges, mask, root, true) == vector<bool>(n, true)) {
              arborescence[root] = min(arborescence[root], cost);
            }
          }
        }
      }
      auto sorted = edges;
      // 非連結・負辺・自己ループ・多重辺を含め、元の連結性を保つ最小コストの森と比較する。
      assert(kruskal(n, sorted) == forest);
      for (int root = 0; root < n; ++root) {
        auto result = MinimumCostArborescence(n, root, edges);
        if (arborescence[root] == LLONG_MAX) {
          // 根から全頂点へ届く有向木がなければ空列を返す。
          assert(result.empty());
          continue;
        }
        long long cost = 0;
        vector<int> indegree(n);
        multiset<tuple<int, int, long long>> remaining;
        for (auto e : edges) {
          remaining.emplace(e.src, e.to, e.cost);
        }
        for (auto e : result) {
          auto found = remaining.find({e.src, e.to, e.cost});
          // 復元した辺は、入力に存在する辺を多重度以内で使っている。
          assert(found != remaining.end());
          remaining.erase(found);
          cost += e.cost;
          ++indegree[e.to];
        }
        // 最適値、各頂点の入次数、根からの到達性の3つを独立に確認する。
        assert(cost == arborescence[root]);
        assert((int)result.size() == n - 1);
        for (int v = 0; v < n; ++v) {
          assert(indegree[v] == (v != root));
        }
        assert(reach(n, result, (1U << result.size()) - 1, root, true) == vector<bool>(n, true));
      }
    }
  }
}
