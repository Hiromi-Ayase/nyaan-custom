#pragma once

#include <functional>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// unreachable -> -1
template <typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>>& g, int start = 0) {
  using P = pair<T, int>;
  int N = (int)g.size();
  vector<T> d(N, T(-1));
  priority_queue<P, vector<P>, greater<P>> Q;
  d[start] = 0;
  Q.emplace(0, start);
  while (!Q.empty()) {
    P p = Q.top();
    Q.pop();
    int cur = p.second;
    if (d[cur] < p.first) {
      continue;
    }
    for (const auto& [dst, weight] : g[cur]) {
      if (d[dst] == T(-1) || d[cur] + weight < d[dst]) {
        d[dst] = d[cur] + weight;
        Q.emplace(d[dst], dst);
      }
    }
  }
  return d;
}

/**
 * @brief ダイクストラ法
 * @docs docs/shortest-path/dijkstra.md
 */
