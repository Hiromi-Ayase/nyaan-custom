// Verify: matrix/polynomial-matrix-tree.hpp
// 全ての辺部分集合から全域木を選び、辺の多項式を筆算した係数和と比較する。
// 非連結・自己ループ・多重辺・零多項式・定数・負の係数を含む。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
#include "matrix/polynomial-matrix-tree.hpp"

using M = ModInt<998244353>;
using F = FormalPowerSeries<M>;

int main() {
  mt19937 rng(610);
  for (int n = 2; n <= 6; ++n) {
    for (int trial = 0; trial < 40; ++trial) {
      PolynomialMatrixTree<M> tree(n - 1);
      vector<tuple<int, int, vector<M>>> edges;
      int m = trial == 0 ? 0 : rng() % 11;
      for (int i = 0; i < m; ++i) {
        int u = rng() % n;
        int v = rng() % n;
        int length = trial == 1 ? 1 : rng() % 4;
        vector<M> weight(length);
        for (auto& x : weight) {
          x = int(rng() % 7) - 3;
        }
        edges.emplace_back(u, v, weight);
        tree.add(u, v, F(weight.begin(), weight.end()));
      }

      vector<M> expected;
      for (int mask = 0; mask < (1 << m); ++mask) {
        if (__builtin_popcount((unsigned)mask) != n - 1) {
          continue;
        }
        vector<vector<int>> g(n);
        vector<M> product{1};
        for (int i = 0; i < m; ++i) {
          if (!(mask >> i & 1)) {
            continue;
          }
          const auto& [u, v, weight] = edges[i];
          g[u].push_back(v);
          g[v].push_back(u);
          if (product.empty() || weight.empty()) {
            product.clear();
            continue;
          }
          vector<M> next(product.size() + weight.size() - 1);
          for (int a = 0; a < (int)product.size(); ++a) {
            for (int b = 0; b < (int)weight.size(); ++b) {
              next[a + b] += product[a] * weight[b];
            }
          }
          product = next;
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
        if ((int)queue.size() != n) {
          continue;
        }
        expected.resize(max(expected.size(), product.size()));
        for (int i = 0; i < (int)product.size(); ++i) {
          expected[i] += product[i];
        }
      }
      auto got = tree.calc();
      while (!expected.empty() && expected.back() == M(0)) {
        expected.pop_back();
      }
      while (!got.empty() && got.back() == M(0)) {
        got.pop_back();
      }
      // 行列式やFPSの乗算を使わずに列挙した、全域木の重み和の全係数と一致する。
      assert(vector<M>(got.begin(), got.end()) == expected);
    }
  }
}
