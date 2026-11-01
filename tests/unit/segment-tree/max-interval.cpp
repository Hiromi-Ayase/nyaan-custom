// Verify: segment-tree/segment-tree-max-of-interval.hpp
// 全区間の和を列挙して、最大/最小部分列・接頭辞・接尾辞と任意の分割位置での結合を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "segment-tree/segment-tree-max-of-interval.hpp"

using M = MaxInterval<long long>;

M reference(const vector<long long>& a) {
  M r;
  if (a.empty()) {
    return r;
  }
  r.num = a.size();
  r.sum = accumulate(a.begin(), a.end(), 0LL);
  r.max = r.lmax = r.rmax = LLONG_MIN;
  r.min = r.lmin = r.rmin = LLONG_MAX;
  for (int l = 0; l < (int)a.size(); ++l) {
    long long sum = 0;
    for (int right = l; right < (int)a.size(); ++right) {
      sum += a[right];
      r.max = max(r.max, sum);
      r.min = min(r.min, sum);
      if (l == 0) {
        r.lmax = max(r.lmax, sum);
        r.lmin = min(r.lmin, sum);
      }
      if (right + 1 == (int)a.size()) {
        r.rmax = max(r.rmax, sum);
        r.rmin = min(r.rmin, sum);
      }
    }
  }
  return r;
}

int main() {
  mt19937 rng(1203);
  for (int n = 0; n <= 30; ++n) {
    for (int trial = 0; trial < 100; ++trial) {
      vector<long long> a(n);
      for (auto& x : a) {
        x = (int)(rng() % 11) - 5;
      }
      auto expected = reference(a);
      for (int split = 0; split <= n; ++split) {
        auto left = reference(vector<long long>(a.begin(), a.begin() + split));
        auto right = reference(vector<long long>(a.begin() + split, a.end()));
        // 全ての分割位置で、結合結果が全区間の直接列挙と一致する。
        assert(merge(left, right) == expected);
      }
      long long x = (int)(rng() % 11) - 5;
      // 定数列用コンストラクタも、空列・全負・全正の境界を含めて一致する。
      assert(M(x, n) == reference(vector<long long>(n, x)));
    }
  }
}
