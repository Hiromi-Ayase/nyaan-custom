// Verify: string/rolling-hash-on-segment-tree.hpp
// 文字列を直接書き換え、各更新後にsubstrの完全一致と比較する。
// 空列・空区間・同一区間・異なる長さ・2の冪の前後を含める。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "string/rolling-hash-on-segment-tree.hpp"

int main() {
  mt19937 rng(7741);
  for (int n : {0, 1, 2, 31, 32, 33, 100}) {
    string s(n, 'a');
    RollingHashonSegmentTree<string> hash(s);
    for (int step = 0; step < 2000; ++step) {
      if (n && step % 3 == 0) {
        int i = rng() % n;
        s[i] = 'a' + rng() % 4;
        hash.update(i, s[i]);
      }

      int l = rng() % (n + 1);
      int r = rng() % (n + 1);
      int u = rng() % (n + 1);
      int v = rng() % (n + 1);
      if (l > r) {
        swap(l, r);
      }

      if (u > v) {
        swap(u, v);
      }

      // 文字の更新後も、2区間の一致判定が実際に切り出した部分文字列の比較と一致する。
      assert(hash.same(l, r, u, v) == (s.substr(l, r - l) == s.substr(u, v - u)));

      // 空区間を含め、同じ区間同士の比較は常に一致する。
      assert(hash.same(l, r, l, r));
    }
  }
}
