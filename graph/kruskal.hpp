#pragma once

#include <algorithm>
#include <tuple>
#include <vector>

#include "../data-structure/union-find.hpp"
using namespace std;

template <typename T>
T kruskal(int N, vector<tuple<int, int, T>>& es) {
  sort(begin(es), end(es), [](const auto& a, const auto& b) { return get<2>(a) < get<2>(b); });
  UnionFind uf(N);
  T ret = 0;
  for (const auto& [src, to, cost] : es) {
    if (uf.same(src, to)) {
      continue;
    }
    ret += cost;
    uf.unite(src, to);
  }
  return ret;
}

/**
 * @docs docs/graph/kruskal.md
 */
