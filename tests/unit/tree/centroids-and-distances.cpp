// Verify: tree/centroid.hpp
// Verify: tree/centroid-decomposition.hpp
// Verify: tree/frequency-table-of-tree-distance.hpp
// 頂点を除いた成分サイズで重心を選び、全始点BFSで距離ごとの頂点対数を計算する。
#include <bits/stdc++.h>
using namespace std;
#include "tree/centroid.hpp"
#include "tree/centroid-decomposition.hpp"
#include "tree/frequency-table-of-tree-distance.hpp"

int main() {
  mt19937 rng(1002);
  for (int n : {1, 2, 3, 4, 7, 16, 31, 64, 129, 257}) {
    for (int shape = 0; shape < 3; ++shape) {
      vector<vector<int>> g(n);
      for (int u = 1; u < n; ++u) {
        int p = shape == 0 ? u - 1 : shape == 1 ? 0 : rng() % u;
        g[u].push_back(p);
        g[p].push_back(u);
      }
      auto pieces = [&](const set<int>& vertices, int removed) {
        set<set<int>> result;
        set<int> seen{removed};
        for (int s : vertices) {
          if (seen.count(s)) {
            continue;
          }
          set<int> part{s};
          vector<int> q{s};
          seen.insert(s);
          for (int i = 0; i < (int)q.size(); ++i) {
            for (int v : g[q[i]]) {
              if (vertices.count(v) && !seen.count(v)) {
                seen.insert(v);
                part.insert(v);
                q.push_back(v);
              }
            }
          }
          result.insert(part);
        }
        return result;
      };
      set<int> all;
      for (int u = 0; u < n; ++u) {
        all.insert(u);
      }
      set<int> expected;
      for (int u = 0; u < n; ++u) {
        int largest = 0;
        for (auto& part : pieces(all, u)) {
          largest = max(largest, (int)part.size());
        }
        if (largest <= n / 2) {
          expected.insert(u);
        }
      }
      auto actual = centroid(g);
      // 重心は、その頂点を除いた最大成分が木全体の半分以下となる頂点。
      assert(set<int>(actual.begin(), actual.end()) == expected);
      CentroidDecomposition decomposition(g);
      auto check = [&](auto&& self, int u) -> set<int> {
        set<int> vertices{u};
        set<set<int>> children;
        for (int v : decomposition.tree[u]) {
          auto part = self(self, v);
          children.insert(part);
          vertices.insert(part.begin(), part.end());
        }
        // 分解木の各子の頂点集合は、元の木から重心を除いた連結成分そのものになる。
        assert(children == pieces(vertices, u));
        for (auto& part : children) {
          assert(part.size() <= vertices.size() / 2);
        }
        return vertices;
      };
      assert(check(check, decomposition.root) == all);
      vector<long long> count(n);
      for (int s = 0; s < n; ++s) {
        vector<int> distance(n, -1);
        vector<int> q{s};
        distance[s] = 0;
        for (int i = 0; i < n; ++i) {
          for (int v : g[q[i]]) {
            if (distance[v] == -1) {
              distance[v] = distance[q[i]] + 1;
              q.push_back(v);
            }
          }
        }
        for (int t = s + 1; t < n; ++t) {
          ++count[distance[t]];
        }
      }
      FrequencyTableOfTreeDistance frequency(g);
      auto result = frequency.get();
      result.resize(n);
      // 同一頂点を除く順序なし頂点対を、全点対距離の度数分布と比較する。
      assert(result == count);
    }
  }
}
