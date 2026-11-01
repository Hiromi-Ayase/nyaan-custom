#pragma once

#include <utility>
#include <vector>

#include "../data-structure/radix-heap.hpp"
using namespace std;

// unreachable -> {-1, -1}
template <typename T>
vector<pair<T, int>> dijkstra_restore(const vector<vector<pair<int, T>>>& g, int start = 0) {
  int N = (int)g.size();
  using P = pair<T, int>;
  vector<P> d(N, P{-1, -1});
  RadixHeap<T, int> Q;
  d[start].first = 0;
  Q.push(0, start);
  while (!Q.empty()) {
    auto p = Q.pop();
    int cur = p.second;
    T dc = d[cur].first;
    if (dc < T(p.first)) {
      continue;
    }
    for (const auto& [dst, weight] : g[cur]) {
      if (d[dst].first == T(-1) || dc + weight < d[dst].first) {
        d[dst] = P{dc + weight, cur};
        Q.push(dc + weight, dst);
      }
    }
  }
  return d;
}

/*
 * @brief ダイクストラ法(復元付き)
 * @docs docs/shortest-path/dijkstra-with-restore.md
 */
