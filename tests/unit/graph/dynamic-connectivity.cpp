// Verify: graph/offline-dynamic-connectivity.hpp
// 各時刻の辺集合をコピーし、BFSで連結性を毎回計算し直して追加・削除・重複を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "graph/offline-dynamic-connectivity.hpp"

int main() {
  mt19937 rng(906);
  for (int n = 1; n <= 15; ++n) {
    int q = 150;
    OffLineDynamicConnectivity solver(n, q);
    map<pair<int, int>, int> active;
    vector<vector<vector<bool>>> expected(q, vector<vector<bool>>(n, vector<bool>(n)));
    for (int t = 0; t < q; ++t) {
      int u = rng() % n;
      int v = rng() % n;
      if (u > v) {
        swap(u, v);
      }
      if (active[{u, v}] > 0 && rng() % 2) {
        --active[{u, v}];
        solver.del_edge(t, u, v);
      } else {
        ++active[{u, v}];
        solver.add_edge(t, u, v);
      }
      for (int s = 0; s < n; ++s) {
        vector<int> bfs{s};
        expected[t][s][s] = true;
        for (int i = 0; i < (int)bfs.size(); ++i) {
          for (auto [edge, count] : active) {
            if (count == 0) {
              continue;
            }
            auto [a, b] = edge;
            if (b == bfs[i]) {
              swap(a, b);
            }
            if (a == bfs[i] && !expected[t][s][b]) {
              expected[t][s][b] = true;
              bfs.push_back(b);
            }
          }
        }
      }
    }
    solver.build();
    int calls = 0;
    int active_merges = 0;
    solver.run([&](int, int) { ++active_merges; }, [&](int, int) { --active_merges; },
               [&](int t) {
                 ++calls;
                 int components = 0;
                 for (int u = 0; u < n; ++u) {
                   bool first = true;
                   for (int v = 0; v < u; ++v) {
                     if (expected[t][u][v]) {
                       first = false;
                     }
                   }
                   components += first;
                   for (int v = 0; v < n; ++v) {
                     // その時刻に残る辺だけで行うBFSと、巻き戻しUnionFindの答えを比較する。
                     assert(solver.uf.same(u, v) == expected[t][u][v]);
                   }
                 }
                 // コールバックで管理した併合数も、その時刻の全域森の辺数に等しい。
                 assert(active_merges == n - components);
               });
    // 全時刻を一度ずつ処理し、終了時にはコールバックとUnionFindの状態が巻き戻る。
    assert(calls == q && active_merges == 0);
    for (int u = 0; u < n; ++u) {
      assert(solver.uf.size(u) == 1);
    }
  }
}
