// Verify: data-structure/union-find-with-potential.hpp
// 差分制約を辺として保存し、BFSで求めた相対値を期待値にする。
// 整合する制約と矛盾する制約、負の差、自己制約、連結成分サイズを検証する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/union-find-with-potential.hpp"

int main() {
  mt19937 rng(438);
  for (int n : {1, 2, 9, 30}) {
    UnionFindWithPotential<long long> uf(n);
    vector<vector<pair<int, long long>>> g(n);
    for (int step = 0; step < 500; ++step) {
      int a = rng() % n;
      int b = rng() % n;
      vector<long long> dist(n, LLONG_MAX);
      dist[b] = 0;
      queue<int> q;
      q.push(b);
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [u, w] : g[v]) {
          if (dist[u] == LLONG_MAX) {
            dist[u] = dist[v] + w;
            q.push(u);
          }
        }
      }

      long long w = int(rng() % 101) - 50;
      if (step % 3 == 0 && dist[a] != LLONG_MAX) {
        w = dist[a];
      }

      bool ok = dist[a] == LLONG_MAX || dist[a] == w;

      // 既存の辺をBFSして得たポテンシャル差と矛盾する制約だけが拒否される。
      assert(uf.merge(a, b, w) == ok);
      if (ok) {
        g[b].emplace_back(a, w);
        g[a].emplace_back(b, -w);
      }

      for (int i = 0; i < n; ++i) {
        if (dist[i] != LLONG_MAX) {
          // BFSで到達できた頂点は、UnionFindでも同じ成分に属する。
          assert(uf.same(i, b));

          // ポテンシャル差の向きも含め、BFSで辺の重みを足した距離と一致する。
          assert(uf.diff(i, b) == dist[i]);
        }
      }

      int size = 0;
      vector<int> seen(n);
      q.push(b);
      seen[b] = 1;
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++size;
        for (auto [u, unused] : g[v]) {
          if (!seen[u]) {
            seen[u] = 1;
            q.push(u);
          }
        }
      }

      // 成分サイズが、参照グラフをBFSして訪れた頂点数と一致する。
      assert(uf.size(b) == size);
    }
  }
}
