#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
//
#include "../../template/template.hpp"
//
#include "../../modint/montgomery-modint.hpp"
#include "../../atcoder/lazysegtree.hpp"
using mint = LazyMontgomeryModInt<998244353>;

using AffineSum = pair<mint, mint>;
AffineSum op(AffineSum a, AffineSum b) { return {a.first + b.first, a.second + b.second}; }
AffineSum e() { return {0, 0}; }
AffineSum mapping(AffineSum action, AffineSum value) {
  return {action.first * value.first + action.second * value.second, value.second};
}
AffineSum composition(AffineSum newer, AffineSum older) {
  return {newer.first * older.first, newer.first * older.second + newer.second};
}
AffineSum id() { return {1, 0}; }

using namespace Nyaan;
void Nyaan::solve() {
  ini(N, Q);
  V<AffineSum> a(N, {0, 1});
  rep(i, N) in(a[i].first);
  atcoder::lazy_segtree<AffineSum, op, e, AffineSum, mapping, composition, id> seg(a);

  rep(_, Q) {
    ini(cmd);
    if (!cmd) {
      inl(l, r, b, c);
      seg.apply(l, r, {b, c});
    } else {
      inl(l, r);
      out(seg.prod(l, r).first);
    }
  }
}