#pragma once

#include <map>
#include <ostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

namespace random_graph {

// 無向隣接リストは逆辺も保持する。自己ループは2回登録する。
template <typename T>
vector<tuple<int, int, T>> edge_list(const vector<vector<pair<int, T>>>& g, bool directed = false) {
  vector<tuple<int, int, T>> edges;
  for (int u = 0; u < (int)g.size(); ++u) {
    map<T, bool> unmatched_loop;
    for (const auto& [v, weight] : g[u]) {
      if (directed || u < v) {
        edges.emplace_back(u, v, weight);
      } else if (u == v) {
        // 同じ重みの自己ループを2要素ずつ組にする。隣接順には依存しない。
        bool& unmatched = unmatched_loop[weight];
        if (!unmatched) {
          edges.emplace_back(u, v, weight);
        }
        unmatched = !unmatched;
      }
    }
  }
  return edges;
}

template <typename T>
int edge_count(const vector<vector<pair<int, T>>>& g, bool directed = false) {
  int arcs = 0;
  for (const auto& neighbors : g) {
    arcs += neighbors.size();
  }
  return directed ? arcs : arcs / 2;
}

// 隣接リストの向きをそのまま使う。辺なしは0、多重辺は最後の重み。
template <typename T>
vector<vector<T>> adjacent_matrix(const vector<vector<pair<int, T>>>& g) {
  vector<vector<T>> matrix(g.size(), vector<T>(g.size()));
  for (int u = 0; u < (int)g.size(); ++u) {
    for (const auto& [v, weight] : g[u]) {
      matrix[u][v] = weight;
    }
  }
  return matrix;
}

template <typename T>
void print_matrix(ostream& os, const vector<vector<pair<int, T>>>& g) {
  auto matrix = adjacent_matrix(g);
  for (const auto& row : matrix) {
    for (int i = 0; i < (int)row.size(); ++i) {
      os << row[i] << (i + 1 == (int)row.size() ? '\n' : ' ');
    }
  }
}

template <typename T>
void print_edges(ostream& os, const vector<vector<pair<int, T>>>& g, bool weighted = false,
                 bool directed = false, bool origin_0 = false) {
  for (const auto& [u, v, weight] : edge_list(g, directed)) {
    os << u + !origin_0 << ' ' << v + !origin_0;
    if (weighted) {
      os << ' ' << weight;
    }
    os << '\n';
  }
}

template <typename T>
void print(ostream& os, const vector<vector<pair<int, T>>>& g, bool weighted = false,
           bool directed = false, bool origin_0 = false) {
  os << g.size() << ' ' << edge_count(g, directed) << '\n';
  print_edges(os, g, weighted, directed, origin_0);
}

}  // namespace random_graph

/**
 * @brief 標準隣接リストの辺列変換・出力
 * @docs docs/random_graph/graph.md
 */
