// Verify: segment-tree/rbst-sequence.hpp
// Verify: segment-tree/rbst-segment-tree.hpp
// 可変長列はvector、座標付き木はmapを期待値とし、文字列の順序・代入・分割・複製を確かめる。
#include <bits/stdc++.h>
using namespace std;
#include "segment-tree/rbst-sequence.hpp"
#include "segment-tree/rbst-segment-tree.hpp"

string join(string a, string b) {
  return a + b;
}

string assign_char(string a, char c) {
  return c ? string(a.size(), c) : a;
}

char compose(char old, char newer) {
  return newer ? newer : old;
}

string identity() {
  return "";
}

char no_action() {
  return 0;
}

int main() {
  using Seq = Sequence<string, char, join, assign_char, compose, identity, no_action>;
  mt19937 rng(1208);
  Seq sequence;
  vector<string> values;
  for (int step = 0; step < 6000; ++step) {
    int n = values.size();
    int operation = rng() % 7;
    string value(1, 'a' + rng() % 26);
    int l = rng() % (n + 1);
    int r = rng() % (n + 1);
    if (l > r) {
      swap(l, r);
    }
    if (operation == 0 || n == 0) {
      sequence.insert(l, value);
      values.insert(values.begin() + l, value);
    } else if (operation == 1) {
      sequence.erase(l, r);
      values.erase(values.begin() + l, values.begin() + r);
    } else if (operation == 2) {
      sequence.apply(l, r, value[0]);
      for (int i = l; i < r; ++i) {
        values[i] = value;
      }
    } else if (operation == 3) {
      int index = rng() % n;
      sequence.set_val(index, value);
      values[index] = value;
    } else if (operation == 4) {
      vector<string> tail{value, "X", "Y"};
      Seq other(tail);
      sequence.append(other);
      values.insert(values.end(), tail.begin(), tail.end());
      // appendは右の列の所有権を移し、右側を空にする。
      assert(other.empty());
    } else if (operation == 5) {
      sequence.pop_back();
      values.pop_back();
    } else {
      sequence.push_back(value);
      values.push_back(value);
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
    // 挿入・削除で添字が移動しても、区間結合の順序と列の長さがvectorと一致する。
    assert(sequence.fold(l, r) == expected && sequence.size() == n);
    if (step % 31 == 0) {
      assert(sequence.get_vector() == values);
    }
  }
  sequence.clear();
  using Sparse = RBSTShiftableLazySegmentTree<int, string, char, join, assign_char, compose,
                                              identity, no_action>;
  Sparse sparse;
  map<int, string> reference;
  for (int step = 0; step < 2000; ++step) {
    int key = (int)(rng() % 201) - 100;
    string value(1, 'a' + rng() % 26);
    int l = (int)(rng() % 241) - 120;
    int r = (int)(rng() % 241) - 120;
    if (l > r) {
      swap(l, r);
    }
    switch (step % 5) {
      case 0:
        sparse.set_val(key, value);
        reference[key] = value;
        break;
      case 1:
        sparse.set_val_fast(key, value);
        reference[key] = value;
        break;
      case 2:
        sparse.erase(key);
        reference.erase(key);
        break;
      case 3:
        sparse.apply(l, r, value[0]);
        for (auto& [k, v] : reference) {
          if (l <= k && k < r) {
            v = value;
          }
        }
        break;
      case 4: {
        int offset = (int)(rng() % 11) - 5;
        sparse.shift(offset);
        map<int, string> shifted;
        for (auto [k, v] : reference) {
          shifted[k + offset] = v;
        }
        reference = shifted;
        break;
      }
    }
    string expected;
    for (auto [k, v] : reference) {
      if (l <= k && k < r) {
        expected += v;
      }
    }
    // 座標の一括移動や遅延代入の後も、キー昇順の非可換な区間積になる。
    assert(sparse.fold(l, r) == expected);
    assert(sparse.exist(key) == bool(reference.count(key)));
    if (step % 29 == 0) {
      auto copy = sparse.deepcopy();
      auto before = sparse.make_array();
      copy.set_val(1000, "!");
      // deepcopyした木への変更は元の木に影響しない。
      assert(sparse.make_array() == before && !sparse.exist(1000));
      copy.clear();
      auto [left, right] = sparse.split_by_key(0);
      vector<pair<int, string>> expected_left;
      vector<pair<int, string>> expected_right;
      for (auto [k, v] : reference) {
        if (k < 0) {
          expected_left.emplace_back(k, v);
        } else {
          expected_right.emplace_back(k, v);
        }
      }
      // キーによる分割は境界0を右側へ含み、元の木を空にする。
      assert(sparse.empty() && left.make_array() == expected_left &&
             right.make_array() == expected_right);
      if (left.empty()) {
        sparse = right;
      } else if (right.empty()) {
        sparse = left;
      } else {
        sparse = ordered_merge(left, right);
      }
    }
  }
  sparse.clear();
  RBSTSegmentTree<int, string, join, identity> plain(vector<string>{"a", "b", "c"});
  plain.set_val(1, "B");
  // 遅延・座標シフトを持たない別名でも、同じ非可換モノイドを扱える。
  assert(plain.fold(0, 3) == "aBc");
  plain.clear();
  RBSTLazySegmentTree<int, string, char, join, assign_char, compose, identity, no_action> lazy(
      vector<string>{"a", "b", "c"});
  lazy.apply(0, 2, 'z');
  assert(lazy.fold_all() == "zzc");
  lazy.clear();
}
