#pragma once

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

namespace graph_internal {
// 重みを使わないアルゴリズムは、intとpairのどちらからも行き先を読む。
constexpr int to_vertex(int vertex) {
  return vertex;
}

template <typename T>
constexpr int to_vertex(const pair<int, T>& edge) {
  return edge.first;
}
}  // namespace graph_internal

// 一般のグラフのstからの距離！！！！
// unvisited nodes : d = -1
vector<int> Depth(const vector<vector<int>>& g, int start = 0) {
  int n = g.size();
  vector<int> ds(n, -1);
  ds[start] = 0;
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int c = q.front();
    q.pop();
    int dc = ds[c];
    for (auto& d : g[c]) {
      if (ds[d] == -1) {
        ds[d] = dc + 1;
        q.push(d);
      }
    }
  }
  return ds;
}

// Depth of Rooted Weighted Tree
// unvisited nodes : d = -1
template <typename T>
vector<T> Depth(const vector<vector<pair<int, T>>>& g, int start = 0) {
  vector<T> d(g.size(), -1);
  auto dfs = [&](auto rec, int cur, T val, int par = -1) -> void {
    d[cur] = val;
    for (const auto& [dst, weight] : g[cur]) {
      if (dst == par) {
        continue;
      }
      rec(rec, dst, val + weight, cur);
    }
  };
  dfs(dfs, start, 0);
  return d;
}

// Diameter of Tree
// return value : { {u, v}, length }
pair<pair<int, int>, int> Diameter(const vector<vector<int>>& g) {
  auto d = Depth(g, 0);
  int u = max_element(begin(d), end(d)) - begin(d);
  d = Depth(g, u);
  int v = max_element(begin(d), end(d)) - begin(d);
  return make_pair(make_pair(u, v), d[v]);
}

// Diameter of Weighted Tree
// return value : { {u, v}, length }
template <typename T>
pair<pair<int, int>, T> Diameter(const vector<vector<pair<int, T>>>& g) {
  auto d = Depth(g, 0);
  int u = max_element(begin(d), end(d)) - begin(d);
  d = Depth(g, u);
  int v = max_element(begin(d), end(d)) - begin(d);
  return make_pair(make_pair(u, v), d[v]);
}

// nodes on the path u-v ( O(N) )
template <typename G>
vector<int> Path(const G& g, int u, int v) {
  vector<int> ret;
  int end = 0;
  auto dfs = [&](auto rec, int cur, int par = -1) -> void {
    ret.push_back(cur);
    if (cur == v) {
      end = 1;
      return;
    }
    for (const auto& edge : g[cur]) {
      int dst = graph_internal::to_vertex(edge);
      if (dst == par) {
        continue;
      }
      rec(rec, dst, cur);
      if (end) {
        return;
      }
    }
    if (end) {
      return;
    }
    ret.pop_back();
  };
  dfs(dfs, u);
  return ret;
}

/**
 * @brief グラフユーティリティ
 * @docs docs/graph/graph-utility.md
 */
