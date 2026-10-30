#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include "../../template/template.hpp"

#include "../../modint/montgomery-modint.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using vm = vector<mint>;
using vvm = vector<vm>;
#include "../../modulo/binomial.hpp"
Binomial<mint> C;

#include "../../graph/graph-template.hpp"
#include "../../math/affine-transformation.hpp"
#include "../../atcoder/segtree.hpp"
#include "../../tree/heavy-light-decomposition.hpp"
//
using namespace Nyaan;

using af = Affine<mint>;
af seg_op(af a, af b) { return a * b; }
af seg_rop(af a, af b) { return b * a; }
af seg_e() { return {}; }

void Nyaan::solve() {
  ini(n, q);
  vm a(n), b(n);
  in2(a, b);
  auto g = graph(n, n - 1, false, false);

  HeavyLightDecomposition<vvi> hld(g);

  vector<af> initial(n);
  rep(i, n) initial[hld.idx(i).first] = af(a[i], b[i]);
  atcoder::segtree<af, seg_op, seg_e> seg1(initial);
  atcoder::segtree<af, seg_rop, seg_e> seg2(initial);

  rep(_, q) {
    ini(cmd, x, y, z);
    if (cmd == 0) {
      seg1.set(hld.idx(x).first, af(y, z));
      seg2.set(hld.idx(x).first, af(y, z));
    } else {
      mint ans = z;
      auto f = [&](int l, int r) {
        if (l <= r)
          ans = seg1.prod(l, r)(ans);
        else
          ans = seg2.prod(r, l)(ans);
      };
      hld.path_noncommutative_query(x, y, true, f);
      out(ans);
    }
  }
}
