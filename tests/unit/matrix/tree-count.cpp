// Verify: matrix/matrix-tree.hpp
// 辺集合を全列挙し、n-1辺で連結になる組合せの重みの積を足す。多重辺・自己ループも含む。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modint/modint.hpp"
#include "matrix/matrix-tree.hpp"

using M = ModInt<998244353>;

int main() {
  mt19937 rng(608);
  for (int n = 2; n <= 6; ++n) {
    for (int trial = 0; trial < 80; ++trial) {
      MatrixTree<M> tree(n - 1);
      vector<tuple<int, int, int>> edges;
      int m = rng() % 11;
      for (int i = 0; i < m; ++i) {
        int u = rng() % n;
        int v = rng() % n;
        int weight = rng() % 5;
        edges.emplace_back(u, v, weight);
        tree.add(u, v, M(weight));
      }
      M expected = 0;
      for (int mask = 0; mask < (1 << m); ++mask) {
        if (__builtin_popcount((unsigned)mask) != n - 1) {
          continue;
        }
        vector<vector<int>> g(n);
        M weight = 1;
        for (int i = 0; i < m; ++i) {
          if (mask >> i & 1) {
            auto [u, v, w] = edges[i];
            g[u].push_back(v);
            g[v].push_back(u);
            weight *= w;
          }
        }
        vector<bool> seen(n);
        vector<int> queue{0};
        seen[0] = true;
        for (int i = 0; i < (int)queue.size(); ++i) {
          for (int v : g[queue[i]]) {
            if (!seen[v]) {
              seen[v] = true;
              queue.push_back(v);
            }
          }
        }
        if ((int)queue.size() == n) {
          expected += weight;
        }
      }
      // 行列式を使わない全域木の列挙と比べ、除いた頂点に接続する辺の寄与も確認する。
      assert(tree.calc() == expected);
    }
  }
}
