// Verify: hashmap/hashmap-base.hpp
// Verify: hashmap/hashmap.hpp
// Verify: hashmap/hashset.hpp
// Verify: hashmap/hashmap-unerasable.hpp
// std::map/setと操作列を比較し、再配置・削除済みバケット再利用・全衝突・初期値を調べる。
#include <bits/stdc++.h>
using namespace std;
#include "hashmap/hashmap-base.hpp"
#include "hashmap/hashmap.hpp"
#include "hashmap/hashset.hpp"
#include "hashmap/hashmap-unerasable.hpp"

template <typename Key>
void check(const vector<Key>& keys) {
  HashMap<Key, long long>::r = 314159265358979ULL;
  HashSet<Key>::r = 271828182845904ULL;
  HashMap<Key, long long> actual;
  HashSet<Key> actual_set;
  map<Key, long long> expected;
  set<Key> expected_set;
  mt19937 rng(1301);
  for (int step = 0; step < 10000; ++step) {
    Key key = keys[rng() % keys.size()];
    long long value = rng() % 100000;
    if (step % 4 == 0) {
      actual[key] += value;
      expected[key] += value;
      actual_set.insert(key);
      expected_set.insert(key);
    }
    if (step % 4 == 1) {
      actual.emplace(key, value);
      expected.emplace(key, value);
    }
    if (step % 4 == 2) {
      actual.erase(actual.find(key), false);
      expected.erase(key);
      actual_set.erase(actual_set.find(key), false);
      expected_set.erase(key);
    }
    if (step % 4 == 3) {
      // findとcountは、削除直後・再挿入直後も標準コンテナの有無と一致する。
      assert(actual.contain(key) == bool(expected.count(key)));
      assert(actual_set.count(key) == (int)expected_set.count(key));
      if (expected.count(key)) {
        assert(actual.find(key)->second == expected[key]);
      }
    }
    if (step % 101 == 0) {
      map<Key, long long> enumerated;
      for (auto [k, v] : actual) {
        enumerated.emplace(k, v);
      }
      set<Key> enumerated_set(actual_set.begin(), actual_set.end());
      // ハッシュの走査順に依存せず、内容とサイズを全要素比較する。
      assert(enumerated == expected && actual.size() == (int)expected.size());
      assert(enumerated_set == expected_set && actual_set.size() == (int)expected_set.size());
      // 標準のstd::distanceがイテレータの型情報を使い、全要素を数えられる。
      assert(distance(actual.begin(), actual.end()) == (ptrdiff_t)expected.size());
      assert(distance(actual_set.begin(), actual_set.end()) == (ptrdiff_t)expected_set.size());
    }
    if (step % 911 == 0) {
      actual.reserve(300);
      actual_set.reserve(300);
    }
    if (step % 2003 == 2002) {
      actual.clear();
      actual_set.clear();
      expected.clear();
      expected_set.clear();
    }
  }
  // 縮小の閾値を跨いで末尾から削除する。返されるendは再配置後のコンテナに対応する。
  actual.reserve(1000);
  while (!actual.empty()) {
    // std::prevによる逆方向の移動も、双方向イテレータとして機能する。
    auto last = prev(actual.end());
    auto next = actual.erase(last);
    assert(next == actual.end());
  }
  assert(actual.empty() && actual.begin() == actual.end());
}

unsigned long long collide(const int&) {
  return 0;
}

template <bool fixed>
void collisions() {
  UnerasableHashMap<int, long long, fixed, collide> actual(-7, 1024);
  map<int, long long> expected;
  mt19937 rng(1302);
  for (int step = 0; step < 5000; ++step) {
    int key = (int)(rng() % 501) - 250;
    // getは未登録のキーに初期値を返し、サイズを変えない。
    assert(actual.get(key) == (expected.count(key) ? expected[key] : -7));
    assert(actual.size() == (int)expected.size());
    if (!expected.count(key)) {
      expected[key] = -7;
    }
    actual[key] += step;
    expected[key] += step;
    if (step % 53 == 0) {
      map<int, long long> all;
      actual.enumerate([&](int k, long long v) { all[k] = v; });
      // 全て同じハッシュ値にしても、キーごとの値を失わずに保持する。
      assert(all == expected && actual.contain(key));
    }
    if (step % 1001 == 1000) {
      actual.reset();
      expected.clear();
    }
  }
  actual.clear();
  // clear後はカスタム初期値へ戻る。
  assert(actual.size() == 0 && actual.get(0) == -7);
}

int main() {
  vector<long long> integers{LLONG_MIN, LLONG_MAX, 0};
  vector<pair<int, int>> pairs;
  vector<vector<int>> sequences{{}, {0}, {0, 0}};
  for (int i = -150; i <= 150; ++i) {
    integers.push_back(i);
    pairs.emplace_back(i, i % 7);
    sequences.push_back({i, 0, i % 11});
  }
  check(integers);
  check(pairs);
  check(sequences);
  collisions<false>();
  collisions<true>();
}
