// Verify: tree/static-top-tree-edge-based.hpp
// Verify: tree/static-top-tree-vertex-based.hpp
// 点更新後に木DPをDFSで計算し直す。頂点版は結合順に依存する一次式、辺版は全要素の和を使う。
#include <bits/stdc++.h>
using namespace std;
#include "tree/static-top-tree-edge-based.hpp"
#include "tree/static-top-tree-vertex-based.hpp"

struct Affine {
  long long a;
  long long b;
};

int main() {
  const long long mod = 1000000007;
  mt19937 rng(1005);
  for (int n : {1, 2, 3, 5, 16, 31, 64, 129}) {
    for (int shape = 0; shape < 3; ++shape) {
      vector<vector<int>> g(n);
      for (int u = 1; u < n; ++u) {
        int p = shape == 0 ? u - 1 : shape == 1 ? 0 : rng() % u;
        g[u].push_back(p);
        g[p].push_back(u);
      }
      int root = rng() % n;
      HeavyLightDecomposition hld(g, root);
      vector<long long> weights(n);
      auto vertex = [&](int u) { return Affine{1, weights[u]}; };
      auto compress = [&](Affine p, Affine c) {
        return Affine{p.a * c.a % mod, (p.a * c.b + p.b) % mod};
      };
      auto rake = [&](long long a, long long b) { return a * b % mod; };
      auto edge = [](Affine a) { return a.b; };
      auto add_vertex = [&](long long a, int u) { return Affine{a, weights[u]}; };
      DPonStaticTopTreeVertexBased<decltype(g), Affine, long long, decltype(vertex),
                                   decltype(compress), decltype(rake), decltype(edge),
                                   decltype(add_vertex)>
          dp(hld, vertex, compress, rake, edge, add_vertex);
      auto value = [&](int u) { return weights[u]; };
      auto sum = [](long long a, long long b) { return a + b; };
      DPonStaticTopTree<decltype(g), long long, decltype(value), decltype(sum), decltype(sum)>
          edge_dp(hld, value, sum, sum);
      for (int step = 0; step < 200; ++step) {
        int u = rng() % n;
        weights[u] = rng() % mod;
        dp.update(u);
        edge_dp.update(u);
        auto naive = [&](auto&& self, int v, int parent) -> long long {
          long long product = 1;
          int children = 0;
          for (int child : g[v]) {
            if (child != parent) {
              product = product * self(self, child, v) % mod;
              ++children;
            }
          }
          return (weights[v] + (children ? product : 0)) % mod;
        };
        // dp[v]=値[v]+子DPの積（葉は値のみ）を全頂点で計算し直し、非可換な縦結合を確認する。
        assert(dp.get().b == naive(naive, root, -1));
        // 辺版では根の仮想要素も含め、更新値の総和が直接の配列和と一致する。
        assert(edge_dp.get() == accumulate(weights.begin(), weights.end(), 0LL));
      }
    }
  }
}
