// Verify: data-structure/divide-interval.hpp
// 各ノードが覆う葉を実際に列挙し、range/applyが要求区間を順序通り一度ずつ覆うか比較する。
// pushによる区間加算とupdateによる集約も、単純な配列操作と照合する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/divide-interval.hpp"

int main() {
  for (int n = 0; n <= 65; ++n) {
    DivideInterval div(n);
    vector<vector<int>> leaves(2 * div.B);
    for (int i = 0; i < div.B; ++i) {
      leaves[div.B + i] = {i};
    }

    div.update([&](int p, int l, int r) {
      leaves[p] = leaves[l];
      leaves[p].insert(leaves[p].end(), leaves[r].begin(), leaves[r].end());
    });
    for (int l = 0; l <= n; ++l) {
      for (int r = l; r <= n; ++r) {
        vector<int> got;
        vector<int> expected(r - l);
        iota(expected.begin(), expected.end(), l);
        div.apply(l, r, [&](int v) { got.insert(got.end(), leaves[v].begin(), leaves[v].end()); });

        // 選ばれたノードの葉を順に連結すると、指定した半開区間を重複なく覆う。
        assert(got == expected);
        vector<int> add(2 * div.B);
        for (int v : div.range(l, r)) {
          ++add[v];
        }

        div.push([&](int p, int c) { add[c] += add[p]; });
        for (int i = 0; i < n; ++i) {
          // ノードに加えた値を葉へ伝播すると、区間内の葉だけが1になる。
          assert(add[div.B + i] == (l <= i && i < r));
        }
      }
    }
  }
}
