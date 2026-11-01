// Verify: string/number-of-subsequences.hpp
// 添字集合を全探索し、非空部分列をsetで重複除去した個数と比較する。
// 空列・全要素同一・負数・64bit整数・文字列キーを検証する。
#include <bits/stdc++.h>
using namespace std;
#include "string/number-of-subsequences.hpp"

int main() {
  auto check = [](const auto& a) {
    using Container = decay_t<decltype(a)>;
    int n = a.size();
    set<Container> expected;
    for (int mask = 1; mask < (1 << n); ++mask) {
      Container sub;
      for (int i = 0; i < n; ++i) {
        if ((mask >> i) & 1) {
          sub.push_back(a[i]);
        }
      }
      expected.insert(sub);
    }
    // 添字の選び方による重複を除き、空列を含まない部分列の個数と比較する。
    assert((number_of_subsequences<Container, long long>(a) == (long long)expected.size()));
  };

  mt19937 rng(887);
  for (int n = 0; n <= 14; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      vector<int> a(n);
      for (int& x : a) {
        x = trial == 0 ? 42 : int(rng() % 4) - 2;
      }
      check(a);
    }
  }

  // std::hashが扱う文字・文字列・64bit整数でも、同値な要素だけをまとめる。
  check(string{});
  check(string("abacaba"));
  check(vector<string>{"", "ab", "a", "b", "ab", "", "a"});
  check(vector<long long>{LLONG_MIN, LLONG_MAX, 0, -1, LLONG_MIN, LLONG_MAX});
  vector<int> distinct(14);
  iota(distinct.begin(), distinct.end(), 0);
  check(distinct);

  vector<int> repeated(1000, 42);
  // 全要素が同一なら、長さ1から1000までの1000種類だけになる。
  assert((number_of_subsequences<vector<int>, long long>(repeated) == 1000));
}
