// Verify: tree/heavy-light-decomposition.hpp
// Verify: tree/euler-tour.hpp
// Verify: tree/tree-query.hpp
// Verify: tree/dsu-on-tree.hpp
// Verify: tree/rerooting.hpp
// Verify: tree/convert-tree.hpp
// Verify: tree/centroid.hpp
// Verify: tree/centroid-decomposition.hpp
// Verify: tree/frequency-table-of-tree-distance.hpp
// Verify: tree/rooted-tree-hash.hpp
// Verify: tree/tree-hash.hpp
// Verify: tree/static-top-tree-edge-based.hpp
// Verify: tree/static-top-tree-vertex-based.hpp
// 標準のpair隣接リストを各木アルゴリズムに渡し、親の全探索と全始点BFSで検証する。
#include <bits/stdc++.h>
using namespace std;
#include "tree/heavy-light-decomposition.hpp"
#include "tree/euler-tour.hpp"
#include "tree/tree-query.hpp"
#include "tree/dsu-on-tree.hpp"
#include "tree/rerooting.hpp"
#include "tree/convert-tree.hpp"
#include "tree/centroid.hpp"
#include "tree/centroid-decomposition.hpp"
#include "tree/frequency-table-of-tree-distance.hpp"
#include "tree/rooted-tree-hash.hpp"
#include "tree/tree-hash.hpp"
#include "tree/static-top-tree-edge-based.hpp"
#include "tree/static-top-tree-vertex-based.hpp"

int main() {
  using G = vector<vector<pair<int, long long>>>;
  mt19937 rng(2401);
  for (int n : {1, 2, 3, 7, 16, 31, 64}) {
    for (int shape = 0; shape < 3; ++shape) {
      G g(n);
      vector<vector<long long>> cost(n, vector<long long>(n));
      for (int u = 1; u < n; ++u) {
        int v = shape == 0 ? u - 1 : shape == 1 ? 0 : rng() % u;
        long long w = ((long long)(rng() % 2000001) - 1000000) * (1LL << 20);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        cost[u][v] = w;
        cost[v][u] = w;
      }
      int root = rng() % n;
      vector<vector<int>> hops(n, vector<int>(n, -1));
      vector<vector<long long>> distances(n, vector<long long>(n));
      vector<int> parent(n, -1);
      for (int s = 0; s < n; ++s) {
        vector<int> queue{s};
        hops[s][s] = 0;
        for (int i = 0; i < n; ++i) {
          int u = queue[i];
          for (auto [v, w] : g[u]) {
            if (hops[s][v] >= 0) {
              continue;
            }
            hops[s][v] = hops[s][u] + 1;
            distances[s][v] = distances[s][u] + w;
            if (s == root) {
              parent[v] = u;
            }
            queue.push_back(v);
          }
        }
      }
      auto original = g;
      HeavyLightDecomposition hld(g, root);
      EulerTour tour(g, root);
      Tree tree(g, root);
      auto rooted = rooted_tree(g, root);
      auto inverse = inverse_tree(rooted);
      auto ancestor = [&](int u, int v) {
        while (v != -1 && v != u) {
          v = parent[v];
        }
        return v == u;
      };
      for (int u = 0; u < n; ++u) {
        auto before = original[u];
        auto after = g[u];
        sort(before.begin(), before.end());
        sort(after.begin(), after.end());
        // HLDの並べ替えは、行き先と重みの対応を崩さない。
        assert(before == after);
        vector<pair<int, long long>> expected;
        if (u != root) {
          expected.emplace_back(parent[u], cost[u][parent[u]]);
        }
        // 根付き化と逆辺化は、重みを保ったまま親だけを出辺にする。
        assert(inverse[u] == expected);
        assert(tree.par(u) == parent[u]);
        for (int v = 0; v < n; ++v) {
          int lca = u;
          while (!ancestor(lca, v)) {
            lca = parent[lca];
          }
          // 重みはLCAや辺数による距離には影響せず、親を辿った結果と一致する。
          assert(hld.lca(u, v) == lca && tour.lca(u, v) == lca && tree.lca(u, v) == lca);
          assert(hld.dist(u, v) == hops[u][v]);
        }
      }
      DSUonTree dsu(g, root);
      set<int> active;
      auto update = [&](int u) { active.insert(u); };
      auto clear = [&](int u) { active.erase(u); };
      auto reset = [&] { assert(active.empty()); };
      auto query = [&](int u) {
        set<int> expected;
        for (int v = 0; v < n; ++v) {
          if (ancestor(u, v)) {
            expected.insert(v);
          }
        }
        // DSU on Treeのコールバックには、その頂点の部分木だけが蓄積される。
        assert(active == expected);
      };
      dsu.run(update, query, clear, reset);
      using State = pair<long long, long long>;
      auto merge = [](State a, State b) { return State{a.first + b.first, a.second + b.second}; };
      auto lift = [&](State a, int child, int p) {
        return State{a.first + 1, a.second + (a.first + 1) * cost[child][p]};
      };
      Rerooting<State, G, decltype(merge), decltype(lift)> reroot(g, merge, lift, State{0, 0});
      for (int u = 0; u < n; ++u) {
        // 負の重みも含む木上距離の総和を、全始点BFSの経路和と比較する。
        assert(reroot[u].first == n - 1);
        assert(reroot[u].second == accumulate(distances[u].begin(), distances[u].end(), 0LL));
      }
      set<int> expected_centroids;
      for (int removed = 0; removed < n; ++removed) {
        vector<bool> seen(n);
        seen[removed] = true;
        int largest = 0;
        for (int s = 0; s < n; ++s) {
          if (seen[s]) {
            continue;
          }
          vector<int> queue{s};
          seen[s] = true;
          for (int i = 0; i < (int)queue.size(); ++i) {
            for (auto [v, w] : g[queue[i]]) {
              if (!seen[v]) {
                seen[v] = true;
                queue.push_back(v);
              }
            }
          }
          largest = max(largest, (int)queue.size());
        }
        if (largest <= n / 2) {
          expected_centroids.insert(removed);
        }
      }
      auto centers = centroid(g);
      CentroidDecomposition decomposition(g);
      // 重心は、頂点削除後の最大成分サイズで求めた集合に含まれる。
      assert(set<int>(centers.begin(), centers.end()) == expected_centroids);
      assert(expected_centroids.count(decomposition.root));
      vector<long long> counts(n);
      for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
          ++counts[hops[u][v]];
        }
      }
      FrequencyTableOfTreeDistance frequency(g);
      auto actual_counts = frequency.get();
      actual_counts.resize(n);
      // 頂点対の距離分布は辺数で数え、pairの重みを距離に加えない。
      assert(actual_counts == counts);
      vector<vector<int>> plain(n);
      for (int u = 0; u < n; ++u) {
        for (auto [v, w] : g[u]) {
          plain[u].push_back(v);
        }
      }
      using PlainHash = RootedTreeHash<decltype(plain)>;
      using PairHash = RootedTreeHash<G>;
      PlainHash::xs().clear();
      for (int i = 0; i <= n; ++i) {
        PlainHash::xs().push_back(PlainHash::Hash::set(100003 + i * 7919LL));
      }
      PairHash::xs() = PlainHash::xs();
      PlainHash plain_hash(plain, root);
      PairHash pair_hash(g, root);
      // 同じ乱数基底を使うと、重みを無視した構造のハッシュが一致する。
      assert(plain_hash.hash == pair_hash.hash);
      assert(tree_hash(plain) == tree_hash(g));
      auto value = [](int u) { return (long long)u + 1; };
      auto sum = [](long long a, long long b) { return a + b; };
      DPonStaticTopTree<G, long long, decltype(value), decltype(sum), decltype(sum)> edge_dp(
          hld, value, sum, sum);
      auto add_edge = [](long long a) { return a; };
      auto add_vertex = [&](long long a, int u) { return a + value(u); };
      DPonStaticTopTreeVertexBased<G, long long, long long, decltype(value), decltype(sum),
                                   decltype(sum), decltype(add_edge), decltype(add_vertex)>
          vertex_dp(hld, value, sum, sum, add_edge, add_vertex);
      // 重み付き隣接リストからのTop Tree構築も、全頂点の値を一度ずつ集約する。
      assert(edge_dp.get() == 1LL * n * (n + 1) / 2);
      assert(vertex_dp.get() == 1LL * n * (n + 1) / 2);
    }
  }
}
