#pragma once

#include <algorithm>

#include "../atcoder/segtree.hpp"

template <typename T, T MINF>
struct SegmentTree_RangeMax {
  using S = T;
  static S op(S a, S b) { return std::max(a, b); }
  static S e() { return MINF; }
  using Tree = atcoder::segtree<S, op, e>;
};

template <typename T, T INF>
struct SegmentTree_RangeMin {
  using S = T;
  static S op(S a, S b) { return std::min(a, b); }
  static S e() { return INF; }
  using Tree = atcoder::segtree<S, op, e>;
};

template <typename T>
struct SegmentTree_RangeSum {
  using S = T;
  static S op(S a, S b) { return a + b; }
  static S e() { return T{}; }
  using Tree = atcoder::segtree<S, op, e>;
};

/**
 * @brief 使用頻度の高いセグメント木
 * @docs docs/segment-tree/segment-tree-utility.md
 */
