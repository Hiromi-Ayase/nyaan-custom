#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
//
#include "../../template/template.hpp"
//
#include "../../segment-tree/segment-tree-utility.hpp"
using namespace Nyaan;

using i8 = char;

void Nyaan::solve() {
  inl(N, Q);
  ins(S);
  V<i8> initial(N);
  rep(i, N) initial[i] = S[i] == '1';
  SegmentTree_RangeMax<i8, 0>::Tree seg(initial);
  while (Q--) {
    inl(c, k);
    if (c == 0) {
      seg.set(k, 1);
    } else if (c == 1) {
      seg.set(k, 0);
    } else if (c == 2) {
      out(int(seg.get(k)));
    } else if (c == 3) {
      int ans = seg.max_right(k, [](i8 b) { return !b; });
      if (ans == N) ans = -1;
      out(ans);
    } else if (c == 4) {
      int ans = seg.min_left(k + 1, [](i8 b) { return !b; });
      --ans;
      out(ans);
    }
  }
}