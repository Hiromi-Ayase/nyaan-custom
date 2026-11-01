// Verify: data-structure/persistent-array.hpp
// Verify: data-structure/persistent-queue.hpp
// Verify: data-structure/persistent-union-find.hpp
// 過去の任意バージョンから更新を分岐し、vector/deque/ラベル配列の全コピーと比較する。
// 新しい更新が古いバージョンを変更しないこと、キューの空からの再利用も検証する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/persistent-array.hpp"
#include "data-structure/persistent-queue.hpp"
#include "data-structure/persistent-union-find.hpp"

int main() {
  mt19937 rng(321);
  const int n = 40;
  PersistentArray<long long> array(vector<long long>(n, -7));
  vector<decltype(array.root)> roots{array.root};
  vector<vector<long long>> arrays(1, vector<long long>(n, -7));
  for (int step = 0; step < 500; ++step) {
    int old = rng() % arrays.size();
    int i = rng() % n;
    long long x = int(rng());
    auto v = arrays[old];
    v[i] = x;
    arrays.push_back(v);
    roots.push_back(array.update(roots[old], i, x));
    for (int q = 0; q < 10; ++q) {
      int ver = rng() % roots.size();
      for (int j = 0; j < n; ++j) {
        // 更新元と異なる過去バージョンも参照し、変更が他の版に漏れないことを全コピーと比較する。
        assert(array.get(roots[ver], j) == arrays[ver][j]);
      }
    }
  }

  PersistentQueue<long long> queue;
  vector<deque<long long>> queues(1);
  for (int step = 0; step < 3000; ++step) {
    int old = rng() % queues.size();
    auto v = queues[old];
    if (v.empty() || rng() % 2) {
      long long x = int(rng());
      v.push_back(x);

      // 過去バージョンからpushしても、新しいバージョン番号が順に割り当てられる。
      assert(queue.push(x, old) == (int)queues.size());
    } else {
      auto [x, id] = queue.pop(old);

      // 過去バージョンの先頭値と、新しく生成されたバージョン番号の両方を確認する。
      assert(x == v.front() && id == (int)queues.size());
      v.pop_front();
    }

    queues.push_back(v);
  }

  PersistentUnionFind uf(n);
  vector<decltype(uf.get_root())> ur{uf.get_root()};
  vector<int> initial(n);
  iota(initial.begin(), initial.end(), 0);
  vector<vector<int>> labels{initial};
  for (int step = 0; step < 400; ++step) {
    int old = rng() % ur.size();
    int a = rng() % n;
    int b = rng() % n;
    auto v = labels[old];
    bool changed = v[a] != v[b];

    // 指定した過去の版で別成分だった場合にだけ、併合成功を返す。
    assert(uf.unite(a, b, ur[old]) == changed);
    ur.push_back(changed ? uf.get_root() : ur[old]);
    int from = v[b];
    int to = v[a];
    for (int& x : v) {
      if (x == from) {
        x = to;
      }
    }

    labels.push_back(v);
    for (int q = 0; q < 5; ++q) {
      int ver = rng() % ur.size();
      for (int i = 0; i < n; ++i) {
        // 任意の過去バージョンの成分サイズを、その版のラベル配列で数えた個数と比較する。
        assert(uf.size(i, ur[ver]) ==
               count(labels[ver].begin(), labels[ver].end(), labels[ver][i]));
        for (int j = 0; j < n; ++j) {
          // 任意の過去バージョンの連結性を、その版のラベルの一致で判定した結果と比較する。
          assert(uf.same(i, j, ur[ver]) == (labels[ver][i] == labels[ver][j]));
        }
      }
    }
  }
}
