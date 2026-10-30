#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"

#include "../../template/template.hpp"
//
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

using namespace Nyaan;

void Nyaan::solve() {
  ini(N, Q);
  int I = 0;
  using SegmentTree = SegmentTree_RangeAdd_RangeSum<int>;
  SegmentTree::Tree seg(vector<SegmentTree::S>(N, {I, 1}));
  rep(_, Q) {
    ini(c);
    if (c == 0) {
      ini(s, t, x);
      s--;
      seg.apply(s, t, x);
    } else {
      ini(i);
      i--;
      out(seg.prod(i, i + 1).sum);
    }
  }
}