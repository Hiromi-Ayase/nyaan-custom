#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
//
#include "../../template/template.hpp"
//
#include "../../misc/rng.hpp"
#include "../../atcoder/lazysegtree.hpp"

using namespace Nyaan;

pl op(pl a, pl b) { return {a.first + b.first, a.second + b.second}; }
pl e() { return {0, 0}; }
pl mapping(ll action, pl value) {
  return {value.first + value.second * action, value.second};
}
ll composition(ll newer, ll older) { return newer + older; }
ll id() { return 0; }

using namespace Nyaan;

void Nyaan::solve() {
  int N = 100000;
  int Q = 1000000;
  atcoder::lazy_segtree<pl, op, e, ll, mapping, composition, id> seg(vp(N, pl{0, 1}));

  rep(i, Q) {
    if (rng() & 1) {
      int l, r;
      l = randint(0, N);
      r = randint(0, N);
      if (l > r) swap(l, r);
      r++;
      seg.apply(l, r, randint(0, TEN(6)));
    } else {
      int x = randint(0, N);
      ll v = seg.get(x).first;
      ll w = seg.prod(x, x + 1).first;
      assert(v == w);
    }
  }

  {
    ini(a, b);
    out(a + b);
  }
}