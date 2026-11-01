#pragma once

#include <deque>
#include <utility>
#include <vector>
using namespace std;

// unreachable -> -1
template <typename T>
vector<T> bfs01(const vector<vector<pair<int, T>>>& g, int start = 0) {
  int N = (int)g.size();
  vector<T> d(N, -1);
  vector<int> vis(N, 0);
  deque<int> Q;
  d[start] = 0;
  Q.push_back(start);
  while (!Q.empty()) {
    int cur = Q.front();
    Q.pop_front();
    if (vis[cur]) {
      continue;
    }
    vis[cur] = 1;
    for (const auto& [dst, weight] : g[cur]) {
      if (d[dst] != -1 and d[dst] <= d[cur] + weight) {
        continue;
      }
      d[dst] = d[cur] + weight;
      if (weight == 0) {
        Q.push_front(dst);
      } else {
        Q.push_back(dst);
      }
    }
  }
  return d;
}

/**
 * @docs docs/shortest-path/bfs01.md
 */
