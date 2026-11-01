// Verify: lct/splay-base.hpp
// Verify: lct/reversible-bbst-base.hpp
// Verify: lct/lazy-reversible-bbst-base.hpp
// Verify: lct/splay-reversible.hpp
// Verify: lct/splay-lazy-reversible.hpp
// Splayの列操作をvector/stringで再現し、非可換な結合と遅延代入・反転を混ぜて確認する。
#include <bits/stdc++.h>
using namespace std;
#include "lct/splay-base.hpp"
#include "lct/reversible-bbst-base.hpp"
#include "lct/lazy-reversible-bbst-base.hpp"
#include "lct/splay-reversible.hpp"
#include "lct/splay-lazy-reversible.hpp"

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
  check<LazyReversibleSplayTree<string, char, join, paint, compose, reverse_value>>();

  ReversibleSplayTree<string, join, reverse_value> tree;
  auto root = tree.build(vector<string>{});
  string expected;
  mt19937 rng(2001);
  for (int step = 0; step < 3000; ++step) {
    int n = expected.size();
    int l = rng() % (n + 1);
    int r = rng() % (n + 1);
    if (l > r) {
      swap(l, r);
    }
    if (step % 3 == 0 || n == 0) {
      char c = 'a' + rng() % 26;
      tree.insert(root, l, string(1, c));
      expected.insert(expected.begin() + l, c);
    } else if (step % 3 == 1) {
      tree.reverse(root, l, r);
      reverse(expected.begin() + l, expected.begin() + r);
    } else {
      int i = rng() % n;
      tree.erase(root, i);
      expected.erase(expected.begin() + i);
    }
    // 遅延作用を持たない版でも、反転後の非可換な集約が順序どおりになる。
    assert(tree.fold(root, 0, expected.size()) == expected);
  }
  while (tree.size(root)) {
    tree.erase(root, 0);
  }
}
