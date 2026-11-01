// Verify: data-structure/rollback-union-find.hpp
// 各併合前のラベル配列を丸ごと保存し、undoと任意世代へのrollback後に比較する。
// 同一成分の併合も履歴に含め、snapshotへの復帰と空の履歴までの復帰を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/rollback-union-find.hpp"

int main() {
  mt19937 rng(712);
  const int n = 30;
  RollbackUnionFind uf(n);
  vector<int> initial(n);
  iota(initial.begin(), initial.end(), 0);
  vector<vector<int>> versions{initial};
  for (int step = 0; step < 3000; ++step) {
    if (versions.size() > 1 && rng() % 4 == 0) {
      int state = rng() % versions.size();
      uf.rollback(state);
      versions.resize(state + 1);
    } else {
      auto next = versions.back();
      int a = rng() % n;
      int b = rng() % n;

      // 連結成分が異なるときだけ併合成功を返す。同一成分への操作も履歴には記録される。
      assert(uf.unite(a, b) == (next[a] != next[b]));
      int old = next[b];
      int now = next[a];
      for (int& x : next) {
        if (x == old) {
          x = now;
        }
      }

      versions.push_back(next);
    }

    // 巻き戻し後の状態番号が、保持したラベル配列の履歴数と一致する。
    assert(uf.get_state() == (int)versions.size() - 1);
    auto& v = versions.back();
    for (int i = 0; i < n; ++i) {
      // 現在の版のラベルを数えた成分サイズと一致する。
      assert(uf.size(i) == count(v.begin(), v.end(), v[i]));
      for (int j = 0; j < n; ++j) {
        // 巻き戻し後の全頂点対の連結性が、保存していたラベル配列と一致する。
        assert(uf.same(i, j) == (v[i] == v[j]));
      }
    }

    uf.snapshot();
    uf.unite(0, n - 1);
    uf.rollback();

    // snapshot以後の操作だけを取り消し、保存した状態番号に戻れる。
    assert(uf.get_state() == (int)versions.size() - 1);
  }

  uf.rollback(0);
  for (int i = 0; i < n; ++i) {
    // 最初まで巻き戻すと、全頂点がサイズ1の独立した成分になる。
    assert(uf.size(i) == 1);
  }
}
