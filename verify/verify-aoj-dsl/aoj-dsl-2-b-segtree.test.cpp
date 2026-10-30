#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree-utility.hpp"

using namespace Nyaan;

void Nyaan::solve() {
  ini(N, Q);
  SegmentTree_RangeSum<int>::Tree seg(N);
  rep(_, Q) {
    ini(c);
    if (c == 0) {
      ini(i, a);
      i--;
      seg.set(i, seg.get(i) + a);
    } else {
      ini(x, y);
      x--;
      out(seg.prod(x, y));
    }
  }
}