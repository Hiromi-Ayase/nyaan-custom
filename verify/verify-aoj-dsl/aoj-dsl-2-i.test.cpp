#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I"

#include "../../template/template.hpp"
//
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

using namespace Nyaan;

void Nyaan::solve() {
  ini(N, Q);
  using SegmentTree = SegmentTree_RangeUpdate_RangeSum<ll>;
  SegmentTree::Tree seg(vector<SegmentTree::S>(N, {0, 1}));
  rep(_, Q) {
    ini(c);
    if (c == 0) {
      ini(s, t, x);
      t++;
      seg.apply(s, t, x);
    } else {
      ini(s, t);
      t++;
      out(seg.prod(s, t).sum);
    }
  }
}