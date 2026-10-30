#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
//
#include "../../template/template.hpp"
//
#include "../../misc/rng.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
//
#include "../../atcoder/lazysegtree.hpp"
//
using namespace Nyaan;

pl f(pl a, pl b) { return a + b; }
pl g(ll b, pl a) { return pl{a.fi + a.se * b, a.se}; }
ll h(ll a, ll b) { return a + b; }
pl ti() { return {0, 0}; }
ll ei() { return 0; }

void Nyaan::solve() {
  int N = 100000;

  using SegmentTree = SegmentTree_RangeAdd_RangeSum<ll>;
  SegmentTree::Tree seg1(vector<SegmentTree::S>(N, {0, 1}));
  atcoder::lazy_segtree<pl, f, ti, ll, g, h, ei> seg2(vp(N, pl{0, 1}));

  int Q = 1000000;
  ll sm = 0;
  rep(_, Q) {
    if (rng() & 1) {
      int l = rng(0, N - 1);
      int r = rng(0, N - 1);
      if (l > r) swap(l, r);
      r++;
      ll x = rng(0, TEN(4));
      seg1.apply(l, r, x);
      seg2.apply(l, r, x);
      sm += (r - l) * x;
    } else {
      int x = randint(0, N - 1);
      ll v = rng(0, 1) ? seg1.get(x).sum : seg1.prod(x, x + 1).sum;
      ll w = rng(0, 1) ? seg2.get(x).fi : seg2.prod(x, x + 1).fi;
      assert(v == w);
    }
    {
      ll i = rng(0, N - 1);
      ll x = max<ll>(1, sm * rnd());
      {
        int v = seg1.max_right(i, [&](SegmentTree::S y) { return y.sum < x; });
        int w = seg2.max_right(i, [&](pl y) { return y.fi < x; });
        assert(v == w);
      }
      {
        int v = seg1.min_left(i, [&](SegmentTree::S y) { return y.sum < x; });
        int w = seg2.min_left(i, [&](pl y) { return y.fi < x; });
        assert(v == w);
      }
    }
  }

  {
    ini(a, b);
    out(a + b);
  }
}
