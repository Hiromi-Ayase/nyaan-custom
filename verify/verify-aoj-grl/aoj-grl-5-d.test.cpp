#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D"

#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree-utility.hpp"
#include "../../tree/heavy-light-decomposition.hpp"
using namespace Nyaan;

void Nyaan::solve() {
  ini(N);
  vvi g(N);
  rep(i, N) {
    ini(n);
    g[i].resize(n);
    in(g[i]);
  }

  HeavyLightDecomposition<vvi> hld(g);
  SegmentTree_RangeSum<int>::Tree seg(N);
  int ans = 0;
  auto q = [&](int u, int v) { ans += seg.prod(u, v); };

  ini(Q);
  rep(_, Q) {
    ini(c);
    if (c == 0) {
      ini(v, w);
      seg.set(hld.idx(v).first, seg.get(hld.idx(v).first) + w);
    } else {
      ini(v);
      ans = 0;
      hld.path_query(0, v,false, q);
      out(ans);
    }
  }
}