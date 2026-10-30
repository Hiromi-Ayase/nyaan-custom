#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree-utility.hpp"
#include "../../tree/heavy-light-decomposition.hpp"

using namespace Nyaan;

void Nyaan::solve() {
  ini(N, Q);
  vl a(N);
  in(a);
  auto g = graph(N, N - 1, false, false);

  HeavyLightDecomposition<vvi> hld(g);
  vl initial(N);
  rep(i, N) initial[hld.idx(i).first] = a[i];
  SegmentTree_RangeSum<ll>::Tree seg(initial);

  ll ans = 0;
  auto que = [&](int u, int v) { ans += seg.prod(u, v); };

  rep(_, Q) {
    ini(cmd, u, v);
    if (cmd) {
      ans = 0;
      hld.path_query(u, v,true, que);
      out(ans);
    } else {
      seg.set(hld.idx(u).first, seg.get(hld.idx(u).first) + v);
    }
  }
}