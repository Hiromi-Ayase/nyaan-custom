#define PROBLEM "https://yukicoder.me/problems/no/2333"
//
#include "../../template/template.hpp"
//
#include "../../segment-tree/segment-tree-max-of-interval.hpp"
#include "../../atcoder/segtree.hpp"

using namespace Nyaan;

using D = MaxInterval<ll>;
D seg_op(D a, D b) { return merge(a, b); }
D seg_e() { return {}; }

void q() {
  inl(N);
  vl A(N), B(N);
  in2(A, B);
  inl(Q);
  vl cmd(Q), X(Q), Y(Q);
  in3(cmd, X, Y);

  vl p{0};
  for (ll i = 0, s = 0; i < N; i++) {
    s += B[i];
    p.push_back(s);
  }
  rep(i, Q) {
    if (cmd[i] == 1) {
      X[i]--;
      p.push_back(X[i]);
      p.push_back(X[i] + 1);
    } else {
      X[i]--;
      p.push_back(X[i]);
      p.push_back(Y[i]);
    }
  }
  p = mkuni(p);

  V<D> init(sz(p) - 1);
  for (ll i = 0, j = 0, s = 0; i < N; i++) {
    s += B[i];
    while (p[j] < s) {
      init[j] = D{A[i], p[j + 1] - p[j]};
      j++;
    }
  }
  atcoder::segtree<D, seg_op, seg_e> seg(init);
  rep(i, Q) {
    ll x = X[i], y = Y[i];
    if (cmd[i] == 1) {
      int j = lb(p, x);
      seg.set(j, D{Y[i], p[j + 1] - p[j]});
    } else {
      ll ans = seg.prod(lb(p, x), lb(p, y)).max;
      out(ans);
    }
  }
}

void Nyaan::solve() {
  int t = 1;
  // in(t);
  while (t--) q();
}
