// Verify: tree/heavy-light-decomposition.hpp
// Verify: tree/euler-tour.hpp
// Verify: tree/tree-query.hpp
// Verify: tree/auxiliary-tree.hpp
// Verify: tree/dsu-on-tree.hpp
// Verify: tree/convert-tree.hpp
// Verify: tree/rerooting.hpp
// 親を1辺ずつたどる全探索でLCA・パス・部分木を求め、区間分解と各種木DPを比較する。
#include <bits/stdc++.h>
using namespace std;
#include "tree/heavy-light-decomposition.hpp"
#include "tree/euler-tour.hpp"
#include "tree/tree-query.hpp"
#include "tree/auxiliary-tree.hpp"
#include "tree/dsu-on-tree.hpp"
#include "tree/convert-tree.hpp"
#include "tree/rerooting.hpp"

int main() {
  mt19937 rng(1001);
  for (int n = 1; n <= 50; ++n) {
    for (int shape = 0; shape < 3; ++shape) {
      vector<vector<int>> g(n);
      for (int u = 1; u < n; ++u) {
        int p = shape == 0 ? u - 1 : shape == 1 ? 0 : rng() % u;
        g[u].push_back(p);
        g[p].push_back(u);
      }
      int root = rng() % n;
      vector<int> parent(n, -1);
      vector<int> depth(n, -1);
      vector<int> order{root};
      depth[root] = 0;
      for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : g[u]) {
          if (depth[v] != -1) {
            continue;
          }
          parent[v] = u;
          depth[v] = depth[u] + 1;
          order.push_back(v);
        }
      }
      auto ancestor = [&](int a, int b) {
        while (b != -1 && b != a) {
          b = parent[b];
        }
        return b == a;
      };
      auto lca = [&](int u, int v) {
        while (!ancestor(u, v)) {
          u = parent[u];
        }
        return u;
      };
      auto rooted = rooted_tree(g, root);
      auto inverse = inverse_tree(rooted);
      HeavyLightDecomposition hld(g, root);
      EulerTour tour(g, root);
      Tree tree(g, root);
      AuxiliaryTree aux(g, root);
      vector<int> inverse_index(n);
      for (int u = 0; u < n; ++u) {
        inverse_index[hld.down[u]] = u;
      }
      vector<long long> vertex_values(2 * n);
      vector<long long> edge_values(2 * n);
      for (int u = 0; u < n; ++u) {
        auto [in, out] = tour.idx(u);
        vertex_values[in] += u + 1;
        vertex_values[out] -= u + 1;
        if (u != root) {
          edge_values[in] += u + 1;
          edge_values[out] -= u + 1;
        }
        // 根付き木は親向きの辺を除き、逆辺の木では根以外の出辺が親1つだけになる。
        assert(inverse[u] == (u == root ? vector<int>{} : vector<int>{parent[u]}));
        for (int v : rooted[u]) {
          assert(parent[v] == u);
        }
        assert(tree.par(u) == parent[u] && tree.depth(u) == depth[u]);
        int a = u;
        for (int k = 0; k <= n; ++k) {
          // k回だけ親をたどった答えと、ダブリングによる祖先を比較する。
          assert(tree.kth_ancestor(u, k) == a);
          if (a != -1) {
            a = parent[a];
          }
        }
      }
      for (int u = 0; u < n; ++u) {
        set<int> subtree;
        for (int v = 0; v < n; ++v) {
          if (ancestor(u, v)) {
            subtree.insert(v);
          }
        }
        for (bool vertex : {false, true}) {
          set<int> expected = subtree;
          if (!vertex) {
            expected.erase(u);
          }
          set<int> actual;
          hld.subtree_query(u, vertex, [&](int l, int r) {
            for (int i = l; i < r; ++i) {
              actual.insert(inverse_index[i]);
            }
          });
          // HLDの部分木区間は、親鎖で判定した子孫を過不足なく含む。
          assert(actual == expected);
        }
        auto [left, right] = tour.idx(u);
        for (int v = 0; v < n; ++v) {
          // EulerTourの入時刻が部分木区間内にあることと子孫関係は同値。
          assert((left <= tour.idx(v).first && tour.idx(v).first < right) ==
                 bool(subtree.count(v)));
        }
        for (int v = 0; v < n; ++v) {
          int common = lca(u, v);
          vector<int> path;
          for (int a = u; a != common; a = parent[a]) {
            path.push_back(a);
          }
          path.push_back(common);
          vector<int> tail;
          for (int a = v; a != common; a = parent[a]) {
            tail.push_back(a);
          }
          reverse(tail.begin(), tail.end());
          path.insert(path.end(), tail.begin(), tail.end());
          // 3種類のLCA実装と経路復元を、親鎖による直接計算と比較する。
          assert(hld.lca(u, v) == common && tour.lca(u, v) == common && tree.lca(u, v) == common);
          assert(tree.path(u, v) == path && hld.dist(u, v) == (int)path.size() - 1);
          if (u != v) {
            assert(tree.nxt(u, v) == path[1]);
          }
          for (int k = 0; k <= (int)path.size(); ++k) {
            // 経路外のジャンプは-1、経路内なら列のk番目となる。
            assert(tree.jump(u, v, k) == (k == (int)path.size() ? -1 : path[k]));
          }
          for (bool vertex : {false, true}) {
            vector<int> expected = path;
            if (!vertex) {
              expected.erase(find(expected.begin(), expected.end(), common));
            }
            vector<int> actual;
            hld.path_noncommutative_query(u, v, vertex, [&](int l, int r) {
              if (l <= r) {
                for (int i = l; i < r; ++i) {
                  actual.push_back(inverse_index[i]);
                }
              } else {
                for (int i = l - 1; i >= r; --i) {
                  actual.push_back(inverse_index[i]);
                }
              }
            });
            // 非可換クエリでは、頂点集合だけでなく始点から終点への順序まで一致する。
            assert(actual == expected);
            actual.clear();
            hld.path_query(u, v, vertex, [&](int l, int r) {
              for (int i = l; i < r; ++i) {
                actual.push_back(inverse_index[i]);
              }
            });
            sort(actual.begin(), actual.end());
            sort(expected.begin(), expected.end());
            // 可換版でも辺/頂点を重複せず過不足なく処理する。
            assert(actual == expected);
          }
          long long vertex_sum = 0;
          long long edge_sum = 0;
          tour.node_query(u, v, [&](int l, int r) {
            vertex_sum += accumulate(vertex_values.begin() + l, vertex_values.begin() + r, 0LL);
          });
          tour.edge_query(u, v, [&](int l, int r) {
            edge_sum += accumulate(edge_values.begin() + l, edge_values.begin() + r, 0LL);
          });
          long long expected = 0;
          for (int a : path) {
            expected += a + 1;
          }
          // 入りで加算・出で減算した配列の区間和が、経路上の頂点/辺の和になる。
          assert(vertex_sum == expected && edge_sum == expected - common - 1);
        }
      }
      DSUonTree dsu(g, root);
      set<int> active;
      vector<int> calls(n);
      auto add = [&](int u) { active.insert(u); };
      auto clear = [&](int u) { active.erase(u); };
      auto reset = [&]() { assert(active.empty()); };
      auto query = [&](int u) {
        ++calls[u];
        set<int> expected;
        for (int v = 0; v < n; ++v) {
          if (ancestor(u, v)) {
            expected.insert(v);
          }
        }
        // DSU on Treeのquery時点では、対象部分木の全頂点だけが保持される。
        assert(active == expected);
      };
      dsu.run(add, query, clear, reset);
      // 各頂点の部分木を一度ずつ処理し、最後のclearで空に戻る。
      assert(calls == vector<int>(n, 1) && active.empty());
      for (int trial = 0; trial < 30; ++trial) {
        vector<int> selected;
        for (int u = 0; u < n; ++u) {
          if (rng() % 4 == 0) {
            selected.push_back(u);
          }
        }
        if (!selected.empty()) {
          selected.push_back(selected[0]);
        }
        auto [small, map] = aux.get(selected);
        set<int> expected(selected.begin(), selected.end());
        for (int u : selected) {
          for (int v : selected) {
            expected.insert(lca(u, v));
          }
        }
        // AuxiliaryTreeの頂点は、指定頂点と全点対LCAだけからなる。
        assert(set<int>(map.begin(), map.end()) == expected);
        int edges = 0;
        for (int i = 0; i < (int)map.size(); ++i) {
          for (int j : small[i]) {
            ++edges;
            // 補助木の親は、採用された祖先のうち元の木で最も深いものになる。
            assert(ancestor(map[i], map[j]));
            for (int a : map) {
              assert(!(a != map[j] && ancestor(a, map[j]) && depth[a] > depth[map[i]]));
            }
          }
        }
        assert(edges == max(0, (int)map.size() - 1));
      }
      using P = pair<long long, long long>;
      auto merge = [](P a, P b) { return P(a.first + b.first, a.second + b.second); };
      auto lift = [](P a, int, int) { return P(a.first + 1, a.second + a.first + 1); };
      Rerooting<P, decltype(g), decltype(merge), decltype(lift)> reroot(g, merge, lift, P(0, 0));
      for (int s = 0; s < n; ++s) {
        vector<int> dist(n, -1);
        vector<int> q{s};
        dist[s] = 0;
        for (int i = 0; i < n; ++i) {
          for (int v : g[q[i]]) {
            if (dist[v] == -1) {
              dist[v] = dist[q[i]] + 1;
              q.push_back(v);
            }
          }
        }
        // 全方位DPによる頂点数・距離和を、全始点からのBFSと比較する。
        assert(reroot[s] == P(n - 1, accumulate(dist.begin(), dist.end(), 0LL)));
      }
    }
  }
}
