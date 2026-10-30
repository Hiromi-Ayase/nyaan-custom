#pragma once

#include <algorithm>
#include <optional>

#include "../atcoder/lazysegtree.hpp"

template <typename T, T MINF>
struct SegmentTree_RangeAdd_RangeMax {
  using S = T;
  using F = T;
  static S op(S a, S b) { return std::max(a, b); }
  static S e() { return MINF; }
  static S mapping(F action, S value) { return value + action; }
  static F composition(F newer, F older) { return newer + older; }
  static F id() { return T{}; }
  using Tree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
};

template <typename T, T INF>
struct SegmentTree_RangeAdd_RangeMin {
  using S = T;
  using F = T;
  static S op(S a, S b) { return std::min(a, b); }
  static S e() { return INF; }
  static S mapping(F action, S value) { return value + action; }
  static F composition(F newer, F older) { return newer + older; }
  static F id() { return T{}; }
  using Tree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
};

template <typename T>
struct SegmentTree_RangeAdd_RangeSum {
  struct S {
    T sum;
    int length;
  };
  using F = T;
  static S op(S a, S b) { return {a.sum + b.sum, a.length + b.length}; }
  static S e() { return {T{}, 0}; }
  static S mapping(F action, S value) {
    return {value.sum + action * value.length, value.length};
  }
  static F composition(F newer, F older) { return newer + older; }
  static F id() { return T{}; }
  using Tree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
};

template <typename T, T MINF>
struct SegmentTree_RangeUpdate_RangeMax {
  using S = T;
  using F = std::optional<T>;
  static S op(S a, S b) { return std::max(a, b); }
  static S e() { return MINF; }
  static S mapping(F action, S value) { return action ? *action : value; }
  static F composition(F newer, F older) { return newer ? newer : older; }
  static F id() { return std::nullopt; }
  using Tree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
};

template <typename T, T INF>
struct SegmentTree_RangeUpdate_RangeMin {
  using S = T;
  using F = std::optional<T>;
  static S op(S a, S b) { return std::min(a, b); }
  static S e() { return INF; }
  static S mapping(F action, S value) { return action ? *action : value; }
  static F composition(F newer, F older) { return newer ? newer : older; }
  static F id() { return std::nullopt; }
  using Tree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
};

template <typename T>
struct SegmentTree_RangeUpdate_RangeSum {
  struct S {
    T sum;
    int length;
  };
  using F = std::optional<T>;
  static S op(S a, S b) { return {a.sum + b.sum, a.length + b.length}; }
  static S e() { return {T{}, 0}; }
  static S mapping(F action, S value) {
    return action ? S{*action * value.length, value.length} : value;
  }
  static F composition(F newer, F older) { return newer ? newer : older; }
  static F id() { return std::nullopt; }
  using Tree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
};

/**
 * @brief 使用頻度の高い遅延セグメント木
 * @docs docs/segment-tree/lazy-segment-tree-utility.md
 */
