#define PROBLEM "https://yukicoder.me/problems/no/2281"
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
  inl(N, Q);
  ins(S);

  atcoder::segtree<D, seg_op, seg_e> seg0(N);
  atcoder::segtree<D, seg_op, seg_e> seg1(N);

  rep(i, N) seg0.set(i, D{S[i] == '0' ? 1 : -inf});
  rep(i, N) seg1.set(i, D{S[i] == '1' ? 1 : -inf});

  vi is1(N);
  rep(i, N) is1[i] = S[i] == '1';
  auto rui = mkrui(is1);

  rep(_, Q) {
    inl(L, R, K);
    L--;
    if (max(seg0.prod(L, R).max, seg1.prod(L, R).max) < K) {
      out(R - L);
      continue;
    }
    ll Y = rui[R] - rui[L];
    ll X = (R - L) - Y;
    while (1) {
      if (X > Y) swap(X, Y);
      ll mn = min(X, Y - (K - 1));
      X -= mn, Y -= mn;
      if (Y < K) break;
      ll ok = 1, ng = Y / K + 1;
      while (ok + 1 < ng) {
        ll med = (ok + ng) / 2;
        ll ny = Y - med * K;
        ll nx = X + med * (K - 1);
        (nx <= ny ? ok : ng) = med;
      }
      Y -= ok * K, X += ok * (K - 1);
    }
    out(X + Y);
  }
}

void Nyaan::solve() {
  int t = 1;
  // in(t);
  while (t--) q();
}
