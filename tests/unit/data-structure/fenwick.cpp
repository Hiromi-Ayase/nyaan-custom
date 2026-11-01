// Verify: data-structure/binary-indexed-tree.hpp
// Verify: data-structure/range-sum-range-add-bit.hpp
// 一点加算・区間加算の結果をvectorへ直接反映し、全区間の和を比較する。
// 閉区間BITと半開区間の区間加算BITの端点を区別し、空区間・負の更新・探索を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/binary-indexed-tree.hpp"
#include "data-structure/range-sum-range-add-bit.hpp"

int main() {
  mt19937 rng(730);
  for (int n : {1, 2, 7, 8, 9, 32}) {
    BinaryIndexedTree<long long> bit(n);
    BinaryIndexedTree<long long> positive(n);
    BinaryIndexedTree<long long> imos(n);
    RangeAddRangeSumBIT<long long> range(n);
    vector<long long> a(n);
    vector<long long> b(n);
    vector<long long> p(n);
    vector<long long> c(n);
    for (int step = 0; step < 200; ++step) {
      int i = rng() % n;
      long long x = int(rng() % 101) - 50;
      bit.add(i, x);
      a[i] += x;
      positive.add(i, abs(x));
      p[i] += abs(x);
      int l = rng() % (n + 1);
      int r = rng() % (n + 1);
      if (l > r) {
        swap(l, r);
      }

      range.add(l, r, x);
      for (int j = l; j < r; ++j) {
        b[j] += x;
      }

      if (l < r) {
        imos.imos(l, r - 1, x);
        for (int j = l; j < r; ++j) {
          c[j] += x;
        }
      }

      for (int j = 0; j < n; ++j) {
        // 点加算の値と区間加算の点取得を、それぞれの素朴な配列と比較する。
        assert(bit[j] == a[j] && imos.sum(j) == c[j]);
      }

      for (int u = 0; u <= n; ++u) {
        for (int v = u; v <= n; ++v) {
          // 閉区間で受け取るBITの和を、対応する配列の半開区間の和と照合する。
          assert(bit.sum(u, v - 1) == accumulate(a.begin() + u, a.begin() + v, 0LL));

          // 区間加算後の区間和を、全要素を更新した配列の和と比較する。
          assert(range.sum(u, v) == accumulate(b.begin() + u, b.begin() + v, 0LL));
        }
      }

      long long total = accumulate(p.begin(), p.end(), 0LL);
      for (long long w : {0LL, 1LL, total / 2, total}) {
        int lower = 0;
        int upper = 0;
        long long sum = p[0];
        while (lower < n && sum < w) {
          ++lower;
          if (lower < n) {
            sum += p[lower];
          }
        }

        sum = p[0];
        while (upper < n && sum <= w) {
          ++upper;
          if (upper < n) {
            sum += p[upper];
          }
        }

        // 非負値の累積和が初めて閾値以上になる位置を、先頭からの走査と比較する。
        assert(positive.lower_bound(w) == lower);
        if (w < total) {
          // 非負値の累積和が初めて閾値を超える位置を、先頭からの走査と比較する。
          assert(positive.upper_bound(w) == upper);
        }
      }
    }
  }
}
