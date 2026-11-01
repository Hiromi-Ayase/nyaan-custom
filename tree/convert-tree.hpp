#pragma once

#include <queue>
#include <type_traits>

#include "../graph/graph-utility.hpp"

template <typename T>
vector<vector<T>> inverse_tree(const vector<vector<T>>& g) {
  int N = (int)g.size();
  vector<vector<T>> rg(N);
  for (int i = 0; i < N; i++) {
    for (auto& e : g[i]) {
      if constexpr (is_same<T, int>::value) {
        rg[e].push_back(i);
      } else {
        const auto& [to, weight] = e;
        rg[to].emplace_back(i, weight);
      }
    }
  }
  return rg;
}

template <typename T>
vector<vector<T>> rooted_tree(const vector<vector<T>>& g, int root = 0) {
  int N = (int)g.size();
  vector<vector<T>> rg(N);
  vector<char> v(N, false);
  v[root] = true;
  queue<int> que;
  que.emplace(root);
  while (!que.empty()) {
    auto p = que.front();
    que.pop();
    for (const auto& e : g[p]) {
      int to = graph_internal::to_vertex(e);
      if (v[to] == false) {
        v[to] = true;
        que.push(to);
        rg[p].push_back(e);
      }
    }
  }
  return rg;
}

/**
 * @brief 根付き木・逆辺からなる木への変換
 * @docs docs/tree/convert-tree.md
 */
