// Verify: segment-tree/persistent-segment-tree.hpp
// Verify: segment-tree/dynamic-segment-tree.hpp
// 全履歴をコピーする配列を永続木の期待値とし、動的木は巨大な座標上のmapと比較する。
#include <bits/stdc++.h>
using namespace std;
#include "segment-tree/persistent-segment-tree.hpp"
#include "segment-tree/dynamic-segment-tree.hpp"

using S = pair<long long, long long>;

S join(S a, S b) {
  return {a.first + b.first, a.second + b.second};
}

S apply(S a, long long x) {
  return {a.first + x * a.second, a.second};
}

long long compose(long long a, long long b) {
  return a + b;
}

S identity() {
  return {0, 0};
}

long long no_action() {
  return 0;
}

int main() {
  mt19937 rng(1204);
  for (int n : {1, 2, 3, 17, 64}) {
    auto concat = [](string a, string b) { return a + b; };
    vector<string> initial(n, ".");
    PersistentSegmentTree<string, decltype(concat), 10000> tree(initial, concat, "");
    vector<vector<string>> versions{initial};
    for (int step = 0; step < 300; ++step) {
      int base = rng() % versions.size();
      int point = rng() % n;
      string value(1, 'a' + rng() % 26);
      auto next = versions[base];
      if (step % 2 == 0) {
        tree.update(base, point, value);
        next[point] = value;
      } else {
        tree.add(tree.roots[base], point, value);
        next[point] = value + next[point];
      }
      versions.push_back(next);
      for (int query = 0; query < 5; ++query) {
        int version = rng() % versions.size();
        int l = rng() % (n + 1);
        int r = rng() % (n + 1);
        if (l > r) {
          swap(l, r);
        }
        string expected;
        for (int i = l; i < r; ++i) {
          expected += versions[version][i];
        }
        // 古い版も含め、非可換な文字列結合が順序どおりで、分岐後の更新が他版へ漏れない。
        assert(tree.query(version, l, r) == expected);
        assert(tree.query(tree.roots[version], l, r) == expected);
      }
    }
    delete[] tree.pool;
  }
  const long long limit = 1LL << 40;
  DynamicLazySegmentTree<S, long long, join, apply, compose, identity, no_action> dynamic(limit);
  DynamicSegmentTree<S, join, identity> plain(limit);
  map<long long, long long> values;
  vector<long long> keys{0, 1, (1LL << 31) - 1, 1LL << 31, limit - 1};
  for (int i = 0; i < 50; ++i) {
    keys.push_back((long long)rng() * 131 % limit);
  }
  for (long long key : keys) {
    dynamic.set_val(key, {0, 1});
    plain.set_val(key, {key % 100, 1});
    values[key] = 0;
  }
  for (int step = 0; step < 1000; ++step) {
    int point = rng() % keys.size();
    long long x = (int)(rng() % 101) - 50;
    long long l = keys[rng() % keys.size()];
    long long r = keys[rng() % keys.size()];
    if (l > r) {
      swap(l, r);
    }
    ++r;
    if (step % 3 == 0) {
      dynamic.set_val(keys[point], {x, 1});
      values[keys[point]] = x;
    } else if (x != 0) {
      dynamic.apply(l, r, x);
      for (auto& [key, value] : values) {
        if (l <= key && key < r) {
          value += x;
        }
      }
    }
    long long expected = 0;
    long long count = 0;
    long long plain_sum = 0;
    for (auto [key, value] : values) {
      if (l <= key && key < r) {
        expected += value;
        ++count;
        plain_sum += key % 100;
      }
    }
    // 未作成部分は長さ0の単位元。登録済み点の和だけを巨大な座標区間で集計する。
    assert(dynamic.fold(l, r) == S(expected, count));
    assert(plain.fold(l, r) == S(plain_sum, count));
    assert(dynamic.get_val(keys[point]) == S(values[keys[point]], 1));
  }
}
