// Verify: data-structure/segment-set.hpp
// 半開区間の追加削除を整数のsetへ展開し、包含・次要素・区間列を比較する。
// 離れた区間、隣接区間の結合、内部を切り抜く削除、負の端点を含める。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/segment-set.hpp"

int main() {
  mt19937 rng(628);
  SegmentSet<int> seg;
  set<int> points;
  for (int step = 0; step < 4000; ++step) {
    int l = int(rng() % 101) - 50;
    int r = int(rng() % 101) - 50;
    if (l > r) {
      swap(l, r);
    }

    if (l == r) {
      ++r;
    }

    if (rng() % 2) {
      seg.insert(l, r);
      for (int x = l; x < r; ++x) {
        points.insert(x);
      }
    } else {
      seg.erase(l, r);
      for (int x = l; x < r; ++x) {
        points.erase(x);
      }
    }

    vector<pair<int, int>> expected;
    for (int x : points) {
      if (expected.empty() || expected.back().second != x) {
        expected.emplace_back(x, x + 1);
      } else {
        ++expected.back().second;
      }
    }

    vector<pair<int, int>> got(seg.begin(), seg.end());

    // 各整数点の集合から作り直した連続区間と比較し、隣接区間の結合や削除後の分割を確認する。
    assert(got == expected);
    for (int x = -55; x <= 55; ++x) {
      // 各整数点の所属が、std::setに登録した点集合と一致する。
      assert((seg.find(x) != seg.end()) == bool(points.count(x)));
      auto it = points.lower_bound(x);

      // 指定値以上の最初の点をstd::setで求め、存在しない場合のINT_MAXも確認する。
      assert(seg.next(x) == (it == points.end() ? INT_MAX : *it));
    }
  }
}
