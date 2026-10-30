#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "../atcoder/segtree.hpp"

// S ... index_type
// T ... value_type
// op, e ... aggregation and identity (AtCoder Library interface)
template <typename S, typename T, T (*op)(T, T), T (*e)()>
struct RangeTree {
  using Seg = atcoder::segtree<T, op, e>;
  using P = std::pair<S, S>;

  S N = 0;
  std::vector<Seg> seg;
  std::vector<std::vector<S>> ys;
  std::vector<P> ps;

  void add_point(S x, S y) { ps.push_back(std::make_pair(x, y)); }

  void build() {
    std::sort(std::begin(ps), std::end(ps));
    ps.erase(std::unique(std::begin(ps), std::end(ps)), std::end(ps));
    N = ps.size();
    seg.assign(2 * N, Seg{});
    ys.assign(2 * N, {});
    for (int i = 0; i < N; ++i) {
      ys[i + N].push_back(ps[i].second);
      seg[i + N] = Seg(1);
    }
    for (int i = N - 1; i > 0; --i) {
      ys[i].resize(ys[i << 1].size() + ys[(i << 1) | 1].size());
      std::merge(std::begin(ys[(i << 1) | 0]), std::end(ys[(i << 1) | 0]),
            std::begin(ys[(i << 1) | 1]), std::end(ys[(i << 1) | 1]), std::begin(ys[i]));
      ys[i].erase(std::unique(std::begin(ys[i]), std::end(ys[i])), std::end(ys[i]));
      seg[i] = Seg(ys[i].size());
    }
  }

  int id(S x) const {
    return std::lower_bound(
               std::begin(ps), std::end(ps), std::make_pair(x, S()),
               [](const P& a, const P& b) { return a.first < b.first; }) -
           std::begin(ps);
  }

  int id(int i, S y) const {
    return std::lower_bound(std::begin(ys[i]), std::end(ys[i]), y) - std::begin(ys[i]);
  }

  void add(S x, S y, T a) {
    int i = std::lower_bound(std::begin(ps), std::end(ps), std::make_pair(x, y)) - std::begin(ps);
    assert(i < N && ps[i] == std::make_pair(x, y));
    for (i += N; i; i >>= 1) {
      int k = id(i, y);
      seg[i].set(k, seg[i].get(k) + a);
    }
  }

  T sum(S xl, S yl, S xr, S yr) {
    T L = e(), R = e();
    int a = id(xl), b = id(xr);
    for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
      if (a & 1) L = op(L, seg[a].prod(id(a, yl), id(a, yr))), ++a;
      if (b & 1) --b, R = op(seg[b].prod(id(b, yl), id(b, yr)), R);
    }
    return op(L, R);
  }
};

/*
 * @brief 領域木(Segment Tree)
 * @docs docs/data-structure-2d/segment-tree-on-range-tree.md
 */
