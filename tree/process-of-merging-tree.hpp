#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "../data-structure/union-find.hpp"
using namespace std;

// マージ過程を表す木
// es の昇順に木をマージしていく。(es にはマージに使わない辺が入っていてよい)
//
// 返り値 : (graph, 補助的な頂点に対応する辺の重み, root)
template <typename T>
tuple<vector<vector<pair<int, T>>>, vector<T>, int> process_of_merging_tree(
    const vector<tuple<int, int, T>>& es) {
  int n = 1;
  for (const auto& [u, v, weight] : es) {
    n = max(n, max(u, v) + 1);
  }

  vector<vector<pair<int, T>>> g(n * 2 - 1);
  vector<T> nodes(n - 1);

  UnionFind uf(n);
  vector<int> roots(n);
  iota(begin(roots), end(roots), 0);
  int aux = n;

  for (const auto& [u, v, w] : es) {
    if (uf.same(u, v)) {
      continue;
    }
    auto f = [&, weight = w](int x, int y) {
      g[aux].emplace_back(roots[x], weight);
      g[aux].emplace_back(roots[y], weight);
      roots[x] = roots[y] = aux;
    };
    uf.unite(u, v, f);
    nodes[aux - n] = w;
    aux++;
  }
  assert(aux == 2 * n - 1);

  return {g, nodes, 2 * n - 2};
}

/**
 * @docs docs/tree/process-of-merging-tree.md
 */
