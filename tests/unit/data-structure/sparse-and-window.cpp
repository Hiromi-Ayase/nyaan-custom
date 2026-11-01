// Verify: data-structure/sparse-table.hpp
// Verify: data-structure/sliding-window-minimum.hpp
// 全区間のminをループで計算し、SparseTableと各窓幅のスライド最小値・最大値を比較する。
// 負数・重複・空区間・幅1・幅N・2の冪付近の長さを確認する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/sparse-table.hpp"
#include "data-structure/sliding-window-minimum.hpp"

int main() {
  mt19937 rng(876);
  for (int n = 0; n <= 70; ++n) {
    vector<int> a(n);
    for (int& x : a) {
      x = int(rng() % 21) - 10;
    }

    SparseTable<int> st(a);
    for (int l = 0; l <= n; ++l) {
      for (int r = l; r <= n; ++r) {
        int expected = SparseTable<int>::INF;
        for (int i = l; i < r; ++i) {
          expected = min(expected, a[i]);
        }

        // 各半開区間の最小値を、区間内の全要素の走査結果と照合する。
        assert(st.query(l, r) == expected);
      }
    }

    for (int k = 1; k <= n; ++k) {
      auto lo = SlideWindowMinimum(a, [](int x, int y) { return min(x, y); }, k);
      auto hi = SlideWindowMinimum(a, [](int x, int y) { return max(x, y); }, k);

      // スライド最小・最大の結果には、空の接頭区間を含めn+1個の位置がある。
      assert(lo.size() == a.size() + 1 && hi.size() == a.size() + 1);
      for (int r = 1; r <= n; ++r) {
        int l = max(0, r - k);

        // 窓幅に満たない先頭部分も含め、該当区間を直接走査した最小値と比較する。
        assert(lo[r] == *min_element(a.begin() + l, a.begin() + r));

        // 比較演算を反転した場合は、該当区間を直接走査した最大値になる。
        assert(hi[r] == *max_element(a.begin() + l, a.begin() + r));
      }
    }
  }
}
