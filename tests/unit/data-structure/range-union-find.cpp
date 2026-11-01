// Verify: data-structure/range-union-find.hpp
// Verify: data-structure/parallel-union-find.hpp
// 区間併合を一組ずつのラベル書き換えに展開して比較する。
// 空区間、同一区間、重なる区間、全体区間を含め、全頂点対の同値関係を調べる。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "data-structure/range-union-find.hpp"
#include "data-structure/parallel-union-find.hpp"

int main() {
  mt19937 rng(919);
  for (int n : {1, 2, 9, 33}) {
    RangeUnionFind range(n);
    ParallelUnionFind parallel(n);
    vector<int> a(n);
    vector<int> b(n);
    iota(a.begin(), a.end(), 0);
    b = a;
    auto merge = [](vector<int>& v, int x, int y) {
      int from = v[y];
      int to = v[x];
      for (int& z : v) {
        if (z == from) {
          z = to;
        }
      }
    };
    for (int step = 0; step < 100; ++step) {
      int len = rng() % (n + 1);
      int l = rng() % (n - len + 1);
      int u = rng() % (n - len + 1);
      range.range_unite(l, l + len);
      for (int i = l + 1; i < l + len; ++i) {
        merge(a, l, i);
      }

      parallel.unite(l, l + len, u, u + len);
      for (int i = 0; i < len; ++i) {
        merge(b, l + i, u + i);
      }

      for (int i = 0; i < n; ++i) {
        // 区間内の全頂点を素朴に併合したラベル配列と、成分サイズを比較する。
        assert(range.size(i) == count(a.begin(), a.end(), a[i]));

        // 2区間の対応位置を1組ずつ併合したラベル配列と、成分サイズを比較する。
        assert(parallel.size(i) == count(b.begin(), b.end(), b[i]));
        for (int j = 0; j < n; ++j) {
          // 区間併合後の全頂点対の連結性が、ラベルの一致と同じになる。
          assert(range.same(i, j) == (a[i] == a[j]));

          // 並列併合後の全頂点対の連結性が、対応位置を逐次併合した結果と一致する。
          assert(parallel.same(i, j) == (b[i] == b[j]));
        }
      }
    }
  }
}
