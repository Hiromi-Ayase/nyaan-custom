#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree-utility.hpp"

using namespace Nyaan;

void Nyaan::solve() {
  ini(N, Q);
  SegmentTree_RangeMin<int, numeric_limits<int>::max()>::Tree seg(N);
  rep(_, Q) {
    ini(c);
    if (c == 0) {
      ini(i, a);
      seg.set(i, a);
    } else {
      ini(x, y);
      y++;
      out(seg.prod(x, y));
    }
  }
}