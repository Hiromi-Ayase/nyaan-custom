// Verify: rbst/rbst-base.hpp
// Verify: rbst/lazy-reversible-rbst.hpp
// Verify: rbst/treap.hpp
// RBSTとTreapの反転・代入・挿入・削除をvectorで再現し、非可換な文字列結合を比較する。
#include <bits/stdc++.h>
using namespace std;
#include "rbst/rbst-base.hpp"
#include "rbst/lazy-reversible-rbst.hpp"
#include "rbst/treap.hpp"

string join(string a, string b) {
  return a + b;
}

string paint(string a, char c) {
  return c ? string(a.size(), c) : a;
}

char compose(char old, char newer) {
  return newer ? newer : old;
}

string reverse_value(string a) {
  reverse(a.begin(), a.end());
  return a;
}

template <typename Tree>
void check() {
  mt19937 rng(1304);
  Tree tree;
  vector<string> values{"a", "b", "c"};
  auto root = tree.build(values);
  for (int step = 0; step < 10000; ++step) {
    int n = values.size();
    int l = rng() % (n + 1);
    int r = rng() % (n + 1);
    if (l > r) {
      swap(l, r);
    }
    int operation = rng() % 5;
    string value(1, 'a' + rng() % 26);
    if (operation == 0 || n == 0) {
      tree.insert(root, l, value);
      values.insert(values.begin() + l, value);
    } else if (operation == 1) {
      int index = rng() % n;
      tree.erase(root, index);
      values.erase(values.begin() + index);
    } else if (operation == 2) {
      tree.reverse(root, l, r);
      reverse(values.begin() + l, values.begin() + r);
    } else if (operation == 3 && l < r) {
      tree.apply(root, l, r, value[0]);
      for (int i = l; i < r; ++i) {
        values[i] = value;
      }
    } else {
      auto [left, right] = tree.split(root, l);
      // 位置による分割は、左にちょうどl個、右に残りの要素を持つ。
      assert(tree.size(left) == l && tree.size(right) == n - l);
      root = tree.merge(left, right);
    }
    n = values.size();
    l = rng() % (n + 1);
    r = rng() % (n + 1);
    if (l > r) {
      swap(l, r);
    }
    string expected;
    for (int i = l; i < r; ++i) {
      expected += values[i];
    }
    // 反転と遅延代入を混ぜても、範囲内の文字の順序がvectorと完全に一致する。
    assert(tree.fold(root, l, r) == expected && tree.size(root) == n);
  }
  while (tree.size(root)) {
    tree.erase(root, 0);
  }
  // 全削除後の空区間は文字列結合の単位元になる。
  assert(tree.fold(root, 0, 0).empty());
}

int main() {
  check<LazyReversibleRBST<string, char, join, paint, compose, reverse_value>>();
  check<LazyReversibleTreap<string, char, join, paint, compose, reverse_value>>();
}
