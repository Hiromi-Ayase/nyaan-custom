// Verify: graph/strongly-connected-components.hpp
// Verify: graph/topological-sort.hpp
// Verify: graph/cycle-detection.hpp
// Verify: math/grundy-number.hpp
// BFSの到達可能性、各辺の前後関係、再帰的mexで有向グラフの分解・閉路・DAGを検証する。
#include <bits/stdc++.h>
using namespace std;
#include "graph/strongly-connected-components.hpp"
#include "graph/topological-sort.hpp"
#include "graph/cycle-detection.hpp"
#include "math/grundy-number.hpp"

int main() {
  mt19937 rng(901);
  for (int n = 0; n <= 7; ++n) {
    for (int trial = 0; trial < 100; ++trial) {
      vector<vector<int>> g(n);
      for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
          if (rng() % 5 == 0 && (trial % 2 == 0 || u < v)) {
            g[u].push_back(v);
          }
        }
      }
      vector<vector<bool>> reach(n, vector<bool>(n));
      bool cyclic = false;
      for (int s = 0; s < n; ++s) {
        queue<int> q;
        q.push(s);
        reach[s][s] = true;
        while (!q.empty()) {
          int u = q.front();
          q.pop();
          for (int v : g[u]) {
            if (v == s) {
              cyclic = true;
            }
            if (!reach[s][v]) {
              reach[s][v] = true;
              q.push(v);
            }
          }
        }
      }
      auto verify = [&](auto& input) {
        StronglyConnectedComponents scc(input);
        vector<int> seen(n);
        multiset<pair<int, int>> expected_edges;
        multiset<pair<int, int>> actual_edges;
        for (int c = 0; c < (int)scc.dag.size(); ++c) {
          for (int u : scc.belong(c)) {
            ++seen[u];
            // belongと頂点からの成分番号が互いに逆の対応になる。
            assert(scc[u] == c);
          }
          for (int d : scc.dag[c]) {
            actual_edges.emplace(c, d);
          }
        }
        for (int u = 0; u < n; ++u) {
          // 孤立点を含め、各頂点がちょうど一つの成分に属する。
          assert(seen[u] == 1);
          for (int v = 0; v < n; ++v) {
            // 同じ強連結成分であることと、相互に到達できることは同値。
            assert((scc[u] == scc[v]) == (reach[u][v] && reach[v][u]));
          }
          for (int v : g[u]) {
            if (scc[u] != scc[v]) {
              expected_edges.emplace(scc[u], scc[v]);
            }
          }
        }
        // 縮約後も成分間の辺が、多重度込みで保存される。
        assert(actual_edges == expected_edges);
        auto cycle = CycleDetection(input);
        // 自己ループを含む閉路の有無が、BFSで始点へ戻れるかと一致する。
        assert(!cycle.empty() == cyclic);
        for (int i = 0; i < (int)cycle.size(); ++i) {
          auto [u, v] = cycle[i];
          // 復元結果は実在する辺が連続した閉じた列である。
          assert(find(g[u].begin(), g[u].end(), v) != g[u].end());
          assert(v == cycle[(i + 1) % cycle.size()].first);
        }
        auto topo = TopologicalSort(input);
        auto grundy = GrundyNumber(g);
        if (cyclic) {
          // DAG専用の二つのAPIは、閉路があれば空列を返す。
          assert(topo.empty() && grundy.empty());
        } else {
          vector<int> position(n);
          // DAGなら全頂点を重複なく列挙する。
          assert((int)topo.size() == n);
          assert(set<int>(topo.begin(), topo.end()).size() == topo.size());
          for (int i = 0; i < n; ++i) {
            position[topo[i]] = i;
          }
          auto mex = [&](auto&& self, int u) -> int {
            set<int> values;
            for (int v : g[u]) {
              values.insert(self(self, v));
            }
            int answer = 0;
            while (values.count(answer)) {
              ++answer;
            }
            return answer;
          };
          for (int u = 0; u < n; ++u) {
            for (int v : g[u]) {
              // 全ての辺で始点が終点より先に現れる。
              assert(position[u] < position[v]);
            }
            // mexをその定義の再帰と集合で計算し、各頂点のGrundy数を比較する。
            assert(grundy[u] == mex(mex, u));
          }
        }
      };
      verify(g);
      vector<vector<pair<int, long long>>> weighted(n);
      for (int u = 0; u < n; ++u) {
        for (int v : g[u]) {
          weighted[u].emplace_back(v, (long long)u * 1000000000 - v);
        }
      }
      // 同じ到達可能性の期待値で、pairの重みを無視した構造も検証する。
      verify(weighted);
    }
  }
}
