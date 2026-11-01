// Verify: orderedmap/orderedmap-base.hpp
// Verify: orderedmap/orderedmap.hpp
// std::mapと全順序の走査で、値・個数・lower/upper_boundの順位・k番目・削除を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "orderedmap/orderedmap-base.hpp"
#include "orderedmap/orderedmap.hpp"

int main() {
  OrderedMap<long long, string> tree;
  map<long long, string> expected;
  mt19937 rng(1303);
  for (int step = 0; step < 10000; ++step) {
    long long key = (int)(rng() % 401) - 200;
    if (step % 37 == 0) {
      key = step % 2 ? LLONG_MAX : LLONG_MIN;
    }
    if (rng() % 3) {
      string value = to_string(step);
      tree[key] = value;
      expected[key] = value;
    } else {
      tree.erase(key);
      expected.erase(key);
    }
    // 境界検索はiteratorではなく順位を返すので、標準mapの先頭からの距離と比べる。
    assert(tree.lower_bound(key) == distance(expected.begin(), expected.lower_bound(key)));
    assert(tree.upper_bound(key) == distance(expected.begin(), expected.upper_bound(key)));
    assert(tree.count(key) == (int)expected.count(key) && tree.size() == (int)expected.size());
    auto found = tree.find(key);
    assert(bool(found) == bool(expected.count(key)));
    if (found) {
      assert(found->val == expected[key]);
    }
    if (step % 29 == 0) {
      int index = 0;
      for (auto [k, v] : expected) {
        auto node = tree.kth_element(index++);
        // 全てのkについて、キー順に並べた要素と値まで一致する。
        assert(node && node->key == k && node->val == v);
      }
      assert(!tree.kth_element(expected.size()));
    }
  }
  while (tree.size()) {
    tree.erase(tree.kth_element(tree.size() / 2));
  }
  // ポインタ指定で消し切った木も、空の状態で境界検索できる。
  assert(tree.lower_bound(0) == 0 && tree.upper_bound(0) == 0 && !tree.find(0));
}
