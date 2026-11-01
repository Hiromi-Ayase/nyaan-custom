// Verify: data-structure/square-root-decomposition.hpp
// 区間加算・区間和を素朴なvector操作と比較する。ブロック実装はこのファイル内に置く。
// 空区間、一ブロック内、複数ブロック、末尾の不完全ブロックと全体の更新を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/square-root-decomposition.hpp"

struct Block {
  using S = long long;
  using T = long long;
  array<long long, 8> a{};
  long long sum = 0;
  long long lazy = 0;

  void init(int) {}

  void update_all(S x) {
    lazy += x;
    sum += x * 8;
  }

  void update_part(int l, int r, S x) {
    for (int i = l; i < r; ++i) {
      a[i] += x;
      sum += x;
    }
  }

  T query_all() {
    return sum;
  }

  T query_part(int l, int r) {
    long long result = lazy * (r - l);
    for (int i = l; i < r; ++i) {
      result += a[i];
    }

    return result;
  }
};

int main() {
  mt19937 rng(751);
  auto add = [](long long a, long long b) { return a + b; };
  for (int n : {0, 1, 7, 8, 9, 31, 32, 33}) {
    SquareRootDecomposition<decltype(add), Block, 8> sq(n, add, 0);
    vector<long long> a(n);
    for (int step = 0; step < 300; ++step) {
      int l = rng() % (n + 1);
      int r = rng() % (n + 1);
      if (l > r) {
        swap(l, r);
      }

      long long x = int(rng() % 101) - 50;
      sq.update(l, r, x);
      for (int i = l; i < r; ++i) {
        a[i] += x;
      }

      for (int u = 0; u <= n; ++u) {
        for (int v = u; v <= n; ++v) {
          // ブロック境界をまたぐ区間加算後の和を、全要素を直接更新した配列の和と比較する。
          assert(sq.query(u, v) == accumulate(a.begin() + u, a.begin() + v, 0LL));
        }
      }
    }
  }
}
