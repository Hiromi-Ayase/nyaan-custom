// Verify: segment-tree/segment-tree-utility.hpp
// Verify: segment-tree/lazy-segment-tree-utility.hpp
// Verify: segment-tree/range-weighted-add-range-sum-lazyseg.hpp
// 通常・区間加算・区間代入・重み付き加算を配列で実行し、空区間を含む和・最小・最大を比べる。
#include <bits/stdc++.h>
using namespace std;
#include "segment-tree/segment-tree-utility.hpp"
#include "segment-tree/lazy-segment-tree-utility.hpp"
#include "segment-tree/range-weighted-add-range-sum-lazyseg.hpp"

int main() {
  const long long inf = 1LL << 60;
  mt19937 rng(1201);
  for (int n : {1, 2, 3, 7, 16, 31, 64, 129}) {
    vector<long long> plain(n);
    vector<long long> added(n);
    vector<long long> assigned(n);
    vector<pair<long long, long long>> weighted(n);
    for (auto& [value, weight] : weighted) {
      value = (int)(rng() % 21) - 10;
      weight = (int)(rng() % 11) - 5;
    }
    SegmentTree_RangeSum<long long>::Tree sum(plain);
    SegmentTree_RangeMin<long long, inf>::Tree minimum(plain);
    SegmentTree_RangeMax<long long, -inf>::Tree maximum(plain);
    using AddSum = SegmentTree_RangeAdd_RangeSum<long long>;
    using SetSum = SegmentTree_RangeUpdate_RangeSum<long long>;
    AddSum::Tree add_sum(vector<AddSum::S>(n, {0, 1}));
    SetSum::Tree set_sum(vector<SetSum::S>(n, {0, 1}));
    SegmentTree_RangeAdd_RangeMin<long long, inf>::Tree add_min(plain);
    SegmentTree_RangeAdd_RangeMax<long long, -inf>::Tree add_max(plain);
    SegmentTree_RangeUpdate_RangeMin<long long, inf>::Tree set_min(plain);
    SegmentTree_RangeUpdate_RangeMax<long long, -inf>::Tree set_max(plain);
    Range_Weighted_Add_Range_Sum_SegTree<pair<long long, long long>, long long> weighted_sum(
        weighted);
    for (int step = 0; step < 500; ++step) {
      int l = rng() % (n + 1);
      int r = rng() % (n + 1);
      if (l > r) {
        swap(l, r);
      }
      long long x = (int)(rng() % 101) - 50;
      int point = rng() % n;
      plain[point] = x;
      sum.set(point, x);
      minimum.set(point, x);
      maximum.set(point, x);
      add_sum.apply(l, r, x);
      add_min.apply(l, r, x);
      add_max.apply(l, r, x);
      set_sum.apply(l, r, x);
      set_min.apply(l, r, x);
      set_max.apply(l, r, x);
      // 重み付き版は非空区間を要求するため、空区間では呼ばない。
      if (l < r) {
        weighted_sum.update(l, r, x);
      }
      for (int i = l; i < r; ++i) {
        added[i] += x;
        assigned[i] = x;
        weighted[i].first += x * weighted[i].second;
      }
      if (step % 7 == 0) {
        weighted[point].first = x;
        weighted_sum.set_val(point, weighted[point]);
      }
      l = rng() % (n + 1);
      r = rng() % (n + 1);
      if (l > r) {
        swap(l, r);
      }
      long long ps = 0;
      long long as = 0;
      long long ss = 0;
      long long ws = 0;
      long long pmin = inf;
      long long pmax = -inf;
      long long amin = inf;
      long long amax = -inf;
      long long smin = inf;
      long long smax = -inf;
      for (int i = l; i < r; ++i) {
        ps += plain[i];
        as += added[i];
        ss += assigned[i];
        ws += weighted[i].first;
        pmin = min(pmin, plain[i]);
        pmax = max(pmax, plain[i]);
        amin = min(amin, added[i]);
        amax = max(amax, added[i]);
        smin = min(smin, assigned[i]);
        smax = max(smax, assigned[i]);
      }
      // 一点代入した配列の区間和・最小・最大と一致し、空区間は各単位元となる。
      assert(sum.prod(l, r) == ps && minimum.prod(l, r) == pmin && maximum.prod(l, r) == pmax);
      // 重なる範囲への加算が全て反映され、長さ情報も保存される。
      assert(add_sum.prod(l, r).sum == as && add_sum.prod(l, r).length == r - l);
      assert(add_min.prod(l, r) == amin && add_max.prod(l, r) == amax);
      // 代入は新しい値が古い値を上書きし、0や負数も作用の単位元と混同しない。
      assert(set_sum.prod(l, r).sum == ss && set_min.prod(l, r) == smin &&
             set_max.prod(l, r) == smax);
      if (l < r) {
        // 各要素の固定重みを掛けた加算と、値の一点代入を比較する。
        assert(weighted_sum.query(l, r) == ws);
      }
      assert(weighted_sum.query(point) == weighted[point].first);
    }
  }
}
