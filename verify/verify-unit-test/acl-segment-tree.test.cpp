#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <string>

#include "../../atcoder/segtree.hpp"
#include "../../atcoder/lazysegtree.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
#include "../../data-structure-2d/segment-tree-on-range-tree.hpp"

using ll = long long;
std::mt19937 rng(20261025);
int pick(int n) { return int(rng() % n); }
std::string concat(std::string a, std::string b) { return a + b; }
std::string empty_string() { return {}; }
ll sum(ll a, ll b) { return a + b; }
ll zero() { return 0; }

void test_segment_tree(int n) {
  std::vector<std::string> a(n, "a");
  atcoder::segtree<std::string, concat, empty_string> seg(a);
  for (int q = 0; q < 200; ++q) {
    if (n) {
      int p = pick(n);
      a[p] = std::string(1, char('a' + pick(4)));
      seg.set(p, a[p]);
      assert(seg.get(p) == a[p]);
    }
    int l = pick(n + 1), r = pick(n + 1);
    if (l > r) std::swap(l, r);
    std::string expected;
    for (int i = l; i < r; ++i) expected += a[i];
    assert(seg.prod(l, r) == expected);
    assert(seg.all_prod() == std::accumulate(a.begin(), a.end(), std::string{}));
    int width = pick(n + 1);
    auto check = [width](std::string s) { return int(s.size()) <= width; };
    assert(seg.max_right(l, check) == std::min(n, l + width));
    assert(seg.min_left(r, check) == std::max(0, r - width));
  }
}

constexpr ll mod = 998244353;
struct Node { ll sum; int length; };
struct Action { ll a, b; };  // No equality operator is required by ACL.
Node op(Node x, Node y) { return {(x.sum + y.sum) % mod, x.length + y.length}; }
Node e() { return {0, 0}; }
Node mapping(Action f, Node x) {
  return {(f.a * x.sum + f.b * x.length) % mod, x.length};
}
Action composition(Action newer, Action older) {
  return {newer.a * older.a % mod, (newer.a * older.b + newer.b) % mod};
}
Action id() { return {1, 0}; }

void test_affine(int n) {
  std::vector<ll> a(n);
  atcoder::lazy_segtree<Node, op, e, Action, mapping, composition, id> seg(
      std::vector<Node>(n, {0, 1}));
  for (int q = 0; q < 400; ++q) {
    int l = pick(n + 1), r = pick(n + 1);
    if (l > r) std::swap(l, r);
    Action f{pick(5), pick(10)};
    int kind = pick(4);
    if (kind == 0 && n) {
      int p = pick(n);
      seg.set(p, {a[p] = pick(100), 1});
    } else if (kind == 1 && n) {
      int p = pick(n);
      seg.apply(p, f);
      a[p] = (f.a * a[p] + f.b) % mod;
    } else {
      if (kind == 2) f = id();
      seg.apply(l, r, f);
      for (int i = l; i < r; ++i) a[i] = (f.a * a[i] + f.b) % mod;
    }
    assert(seg.prod(l, r).sum == std::accumulate(a.begin() + l, a.begin() + r, 0LL) % mod);
    assert(seg.prod(l, r).length == r - l);
    assert(seg.all_prod().sum == std::accumulate(a.begin(), a.end(), 0LL) % mod);
    assert(seg.all_prod().length == n);
    if (n) { int p = pick(n); assert(seg.get(p).sum == a[p]); }
  }
}

void test_presets(int n) {
  constexpr ll inf = 1000000;
  std::vector<ll> a(n), b(n);
  SegmentTree_RangeAdd_RangeMin<ll, inf>::Tree amin(a);
  SegmentTree_RangeAdd_RangeMax<ll, -inf>::Tree amax(a);
  using AddSum = SegmentTree_RangeAdd_RangeSum<ll>;
  AddSum::Tree asum(std::vector<AddSum::S>(n, {0, 1}));
  SegmentTree_RangeUpdate_RangeMin<ll, inf>::Tree bmin(b);
  SegmentTree_RangeUpdate_RangeMax<ll, -inf>::Tree bmax(b);
  using UpdateSum = SegmentTree_RangeUpdate_RangeSum<ll>;
  UpdateSum::Tree bsum(std::vector<UpdateSum::S>(n, {0, 1}));
  for (int q = 0; q < 300; ++q) {
    int l = pick(n + 1), r = pick(n + 1);
    if (l > r) std::swap(l, r);
    ll x = pick(10);
    if (pick(2) && n) {
      int p = pick(n);
      amin.set(p, x); amax.set(p, x); asum.set(p, {x, 1}); a[p] = x;
      bmin.set(p, x); bmax.set(p, x); bsum.set(p, {x, 1}); b[p] = x;
    } else {
      amin.apply(l, r, x); amax.apply(l, r, x); asum.apply(l, r, x);
      for (int i = l; i < r; ++i) a[i] += x;
      // Include the former identity sentinels as real assignment values.
      x = q % 3 == 0 ? inf : q % 3 == 1 ? -inf : x;
      bmin.apply(l, r, x); bmax.apply(l, r, x); bsum.apply(l, r, x);
      for (int i = l; i < r; ++i) b[i] = x;
      bmin.apply(0, n, std::nullopt);
      bmax.apply(0, n, std::nullopt);
      bsum.apply(0, n, std::nullopt);
    }
    int ql = pick(n + 1), qr = pick(n + 1);
    if (ql > qr) std::swap(ql, qr);
    auto lo = [ql, qr](const std::vector<ll>& v) {
      return ql == qr ? inf : *std::min_element(v.begin() + ql, v.begin() + qr);
    };
    auto hi = [ql, qr](const std::vector<ll>& v) {
      return ql == qr ? -inf : *std::max_element(v.begin() + ql, v.begin() + qr);
    };
    assert(amin.prod(ql, qr) == lo(a)); assert(amax.prod(ql, qr) == hi(a));
    assert(bmin.prod(ql, qr) == lo(b)); assert(bmax.prod(ql, qr) == hi(b));
    assert(asum.prod(ql, qr).sum == std::accumulate(a.begin() + ql, a.begin() + qr, 0LL));
    assert(bsum.prod(ql, qr).sum == std::accumulate(b.begin() + ql, b.begin() + qr, 0LL));
    assert(asum.all_prod().sum == std::accumulate(a.begin(), a.end(), 0LL));
    assert(bsum.all_prod().sum == std::accumulate(b.begin(), b.end(), 0LL));
    assert(asum.all_prod().length == n && bsum.all_prod().length == n);
    ll limit = pick(100), acc = 0;
    int right = ql, left = qr;
    while (right < n && acc + a[right] <= limit) acc += a[right++];
    acc = 0;
    while (left > 0 && acc + a[left - 1] <= limit) acc += a[--left];
    auto check = [limit](AddSum::S value) { return value.sum <= limit; };
    assert(asum.max_right(ql, check) == right);
    assert(asum.min_left(qr, check) == left);
  }
}

void test_range_tree() {
  RangeTree<int, ll, sum, zero> tree;
  tree.build();
  assert(tree.sum(-1, -1, 5, 5) == 0);
  for (int x = -2; x <= 2; ++x)
    for (int y = -2; y <= 2; ++y) tree.add_point(x, y);
  tree.build();
  ll a[5][5]{};
  for (int q = 0; q < 500; ++q) {
    int x = pick(5), y = pick(5), delta = pick(21) - 10;
    tree.add(x - 2, y - 2, delta); a[x][y] += delta;
    int xl = pick(6), xr = pick(6), yl = pick(6), yr = pick(6);
    if (xl > xr) std::swap(xl, xr);
    if (yl > yr) std::swap(yl, yr);
    ll expected = 0;
    for (int i = xl; i < xr; ++i) for (int j = yl; j < yr; ++j) expected += a[i][j];
    assert(tree.sum(xl - 2, yl - 2, xr - 2, yr - 2) == expected);
  }
}

int main() {
  for (int n : {0, 1, 2, 3, 5, 8, 17, 31}) {
    test_segment_tree(n);
    test_affine(n);
    test_presets(n);
  }
  test_range_tree();
  ll a, b;
  std::cin >> a >> b;
  std::cout << a + b << '\n';
}
