// Verify: segment-tree/segment-tree-beats.hpp
// Verify: segment-tree/segment-tree-beats-abstract.hpp
// chmin・chmax・加算・代入を配列に直接適用し、抽象版では更新を下へ降ろす必要のある剰余を試す。
#include <bits/stdc++.h>
using namespace std;
#include "segment-tree/segment-tree-beats.hpp"
#include "segment-tree/segment-tree-beats-abstract.hpp"

struct ModNode {
  long long sum = 0;
  long long largest = 0;
  int count = 0;
  ModNode() = default;

  ModNode(long long x) : sum(x), largest(x), count(1) {}

  void update(const ModNode& a, const ModNode& b) {
    sum = a.sum + b.sum;
    largest = max(a.largest, b.largest);
    count = a.count + b.count;
  }

  void push(ModNode&, ModNode&) {}

  bool apply(long long mod) {
    if (largest < mod) {
      return true;
    }
    if (count == 1) {
      sum %= mod;
      largest = sum;
      return true;
    }
    return false;
  }
};

int main() {
  mt19937 rng(1202);
  for (int n : {0, 1, 2, 3, 7, 16, 31, 64, 129}) {
    vector<long long> a(n);
    vector<long long> remainder(n);
    for (int i = 0; i < n; ++i) {
      a[i] = (int)(rng() % 201) - 100;
      remainder[i] = rng() % 1000000;
    }
    AngelBeats tree(a);
    Beats<ModNode> modulo(remainder);
    for (int step = 0; step < 1000; ++step) {
      int l = rng() % (n + 1);
      int r = rng() % (n + 1);
      if (l > r) {
        swap(l, r);
      }
      long long x = (int)(rng() % 201) - 100;
      int operation = rng() % 4;
      if (operation == 0) {
        tree.range_chmin(l, r, x);
      }
      if (operation == 1) {
        tree.range_chmax(l, r, x);
      }
      if (operation == 2) {
        tree.range_add(l, r, x);
      }
      if (operation == 3) {
        tree.range_update(l, r, x);
      }
      for (int i = l; i < r; ++i) {
        if (operation == 0) {
          a[i] = min(a[i], x);
        }
        if (operation == 1) {
          a[i] = max(a[i], x);
        }
        if (operation == 2) {
          a[i] += x;
        }
        if (operation == 3) {
          a[i] = x;
        }
      }
      long long divisor = 1 + rng() % 1000000;
      modulo.apply(l, r, divisor);
      for (int i = l; i < r; ++i) {
        remainder[i] %= divisor;
      }
      l = rng() % (n + 1);
      r = rng() % (n + 1);
      if (l > r) {
        swap(l, r);
      }
      long long sum = accumulate(a.begin() + l, a.begin() + r, 0LL);
      long long minimum = l == r ? AngelBeats::INF : *min_element(a.begin() + l, a.begin() + r);
      long long maximum = l == r ? -AngelBeats::INF : *max_element(a.begin() + l, a.begin() + r);
      // 同じ極値が複数ある場合も含め、4操作を混ぜた後の和・最小・最大が直接計算と一致する。
      assert(tree.range_sum(l, r) == sum && tree.range_min(l, r) == minimum &&
             tree.range_max(l, r) == maximum);
      long long actual = 0;
      modulo.query(l, r, [&](const ModNode& node) { actual += node.sum; });
      // 抽象Beatsがapply=falseで正しく降下し、葉ごとの剰余を集計できることを確認する。
      assert(actual == accumulate(remainder.begin() + l, remainder.begin() + r, 0LL));
    }
  }
}
