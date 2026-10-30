#define PROBLEM "https://judge.yosupo.jp/problem/range_set_range_composite"
//
#include "../../template/template.hpp"
//
#include "../../math/affine-transformation.hpp"
#include "../../atcoder/lazysegtree.hpp"
#include <optional>
//
#include "../../modint/montgomery-modint.hpp"
//
using namespace Nyaan;
using mint = LazyMontgomeryModInt<998244353>;
// using mint = LazyMontgomeryModInt<1000000007>;
using vm = vector<mint>;
using vvm = vector<vm>;

using namespace Nyaan;

using A = Affine<mint>;
using D = pair<A, int>;
using F = optional<A>;
D op(D a, D b) { return {b.first(a.first), a.second + b.second}; }
D e() { return {A{1, 0}, 0}; }
D mapping(F action, D value) {
  return action ? D{Power(*action, value.second, A{1, 0}), value.second} : value;
}
F composition(F newer, F older) { return newer ? newer : older; }
F id() { return nullopt; }

void q() {
  ini(N, Q);

  V<D> v(N, make_pair(A{}, 1));
  rep(i, N) in(v[i].fi.a, v[i].fi.b);

  atcoder::lazy_segtree<D, op, e, F, mapping, composition, id> seg(v);

  rep(i, Q) {
    ini(cmd);
    if (cmd == 0) {
      ini(l, r, c, d);
      seg.apply(l, r, A{c, d});
    } else {
      ini(l, r, x);
      auto a = seg.prod(l, r);
      out(a.fi(x));
    }
  }
}

void Nyaan::solve() {
  int t = 1;
  // in(t);
  while (t--) q();
}
