#pragma once

#include "../graph/graph-utility.hpp"

// restore shortest path from S to G
template <typename T>
vector<int> restore_shortest_path(const vector<vector<pair<int, T>>>& g, const vector<T>& d, int S,
                                  int G) {
  int N = g.size();
  vector<vector<pair<int, T>>> rev(g.size());
  for (int i = 0; i < N; i++) {
    for (const auto& [to, weight] : g[i]) {
      rev[to].emplace_back(i, weight);
    }
  }
  vector<int> ret;
  ret.push_back(G);
  int p = G;
  T dist = d[G];
  vector<int> vis(N, 0);
  vis[G] = 1;
  do {
    int nxt = -1;
    T nval = numeric_limits<T>::max() / 2;
    for (const auto& [to, weight] : rev[p]) {
      if (vis[to] || d[to] + weight != dist) {
        continue;
      }
      if (d[to] != -1 && d[to] < nval) {
        nval = d[to];
        nxt = to;
      }
    }
    vis[nxt] = 1;
    dist = nval;
    p = nxt;
    ret.push_back(p);
  } while (p != S);
  reverse(begin(ret), end(ret));
  return ret;
}

/**
 * @docs docs/shortest-path/restore-shortest-path.md
 */
