// Verify: data-structure/union-find.hpp
// Verify: data-structure/union-find-enumerate.hpp
// Verify: data-structure/dynamic-union-find.hpp
// 連結成分をラベル配列で愚直に管理し、併合後の全頂点対・サイズ・列挙を比較する。
// 自己併合、既に連結な頂点、非連続な大きいID、コールバックの呼び出し回数も確認する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/union-find.hpp"
#include "data-structure/union-find-enumerate.hpp"
#include "data-structure/dynamic-union-find.hpp"

int main() {
  mt19937 rng(901);
  for (int n : {1, 2, 7, 32, 65}) {
    UnionFind uf(n);
    UnionFindEnumerate en(n);
    DynamicUnionFind dyn;
    vector<int> label(n);
    vector<int> key(n);
    iota(label.begin(), label.end(), 0);
    for (int i = 0; i < n; ++i) {
      key[i] = i * 1000003;
    }

    for (int step = 0; step < 300; ++step) {
      int a = rng() % n;
      int b = rng() % n;
      bool changed = label[a] != label[b];
      int callbacks = 0;

      // 異なるラベルの成分を併合した場合にだけ、通常版が成功を返す。
      assert(uf.unite(a, b, [&](int, int) { ++callbacks; }) == changed);

      // コールバックは、成分が実際に併合された場合だけ1回呼ばれる。
      assert(callbacks == changed);

      // 要素列挙版でも、異なる成分を併合した場合にだけ成功を返す。
      assert(en.unite(a, b) == changed);

      // 疎なキーを使う動的版でも、併合の成否はラベル配列と一致する。
      assert(dyn.unite(key[a], key[b]) == changed);
      int old = label[b];
      int now = label[a];
      for (int& x : label) {
        if (x == old) {
          x = now;
        }
      }

      for (int i = 0; i < n; ++i) {
        vector<int> expected;
        for (int j = 0; j < n; ++j) {
          bool same = label[i] == label[j];

          // 通常版の連結判定を、素朴に更新したラベル配列と全頂点対で比較する。
          assert(uf.same(i, j) == same);

          // 要素列挙版でも、全頂点対の連結判定がラベル配列と一致する。
          assert(en.same(i, j) == same);

          // 動的版でも、疎なキーに対応する頂点の連結判定がラベル配列と一致する。
          assert(dyn.same(key[i], key[j]) == same);
          if (same) {
            expected.push_back(j);
          }
        }

        // 通常版の成分サイズは、同じラベルを持つ頂点の個数になる。
        assert(uf.size(i) == (int)expected.size());

        // 要素列挙版の成分サイズも、同じラベルを持つ頂点の個数になる。
        assert(en.size(i) == (int)expected.size());

        // 動的版の成分サイズも、同じラベルを持つ頂点の個数になる。
        assert(dyn.size(key[i]) == (int)expected.size());
        auto got = en.enumerate(i);
        sort(got.begin(), got.end());

        // 成分内の頂点を列挙すると、ラベル配列から選んだ集合と重複なく一致する。
        assert(got == expected);
      }
    }

    dyn.clear();
    for (int x : key) {
      // 動的版で未使用キーを問い合わせると、独立したサイズ1の成分として扱われる。
      assert(dyn.size(x) == 1);
    }
  }
}
