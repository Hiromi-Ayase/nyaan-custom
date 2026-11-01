// Verify: misc/mo.hpp
// Verify: misc/mo-fast.hpp
// Verify: misc/doubling.hpp
// Moの左右コールバックでdequeを作り、ダブリングは1辺ずつの移動と非可換文字列で照合する。
#include <bits/stdc++.h>
using namespace std;
#include "misc/mo.hpp"
#include "misc/mo-fast.hpp"
#include "misc/doubling.hpp"

template <typename Solver>
void check_mo(int n, int queries) {
  mt19937 rng(1402);
  Solver solver(n, queries);
  vector<pair<int, int>> ranges;
  for (int i = 0; i < queries; ++i) {
    int l = rng() % (n + 1);
    int r = rng() % (n + 1);
    if (l > r) {
      swap(l, r);
    }
    ranges.emplace_back(l, r);
    solver.insert(l, r);
  }
  deque<int> active;
  auto al = [&](int i) { active.push_front(i); };
  auto ar = [&](int i) { active.push_back(i); };
  auto dl = [&](int i) {
    assert(!active.empty() && active.front() == i);
    active.pop_front();
  };
  auto dr = [&](int i) {
    assert(!active.empty() && active.back() == i);
    active.pop_back();
  };
  vector<int> calls(queries);
  auto query = [&](int i) {
    ++calls[i];
    vector<int> expected;
    for (int j = ranges[i].first; j < ranges[i].second; ++j) {
      expected.push_back(j);
    }
    // 左右の追加・削除の順序まで含め、query時点の列が指定した半開区間そのものになる。
    assert(vector<int>(active.begin(), active.end()) == expected);
  };
  solver.run(al, ar, dl, dr, query);
  // 同一区間が重複しても、全クエリをそれぞれ一度ずつ処理する。
  assert(calls == vector<int>(queries, 1));
}

int main() {
  for (int n : {0, 1, 3, 16, 65, 200}) {
    for (int q : {1, 2, 3, 17, 100}) {
      check_mo<Mo>(n, q);
      check_mo<Fast_Mo>(n, q);
    }
    check_mo<Mo>(n, 0);
  }
  mt19937 rng(1403);
  for (int n = 1; n <= 30; ++n) {
    vector<int> next(n);
    vector<string> edge(n);
    Doubling<string> doubling(n, 255, "");
    for (int i = 0; i < n; ++i) {
      next[i] = (int)(rng() % (n + 1)) - 1;
      edge[i] = next[i] == -1 ? "" : string(1, 'a' + i % 26);
      doubling.set_next(i, next[i], edge[i]);
    }
    doubling.build();
    for (int start = 0; start < n; ++start) {
      int vertex = start;
      string path;
      for (int steps = 0; steps <= 255; ++steps) {
        // 1辺ずつたどった終点と文字列を比較し、存在しない遷移の後は停止する。
        assert(doubling.query(start, steps) == make_pair(vertex, path));
        if (steps > 0 && (steps & (steps - 1)) == 0) {
          assert(doubling.query_pow(start, __builtin_ctz((unsigned)steps)) ==
                 make_pair(vertex, path));
        }
        if (vertex != -1) {
          path += edge[vertex];
          vertex = next[vertex];
        }
      }
    }
    Doubling<long long> forward(n, n);
    for (int i = 0; i < n; ++i) {
      forward.set_next(i, i + 1 < n ? i + 1 : -1, i + 1 < n ? i + 1 : 0);
    }
    forward.build();
    for (int start = 0; start < n; ++start) {
      for (int limit = start; limit < n; ++limit) {
        long long sum = 0;
        for (int i = start + 1; i <= limit; ++i) {
          sum += i;
        }
        auto result = forward.binary_search(start, limit);
        // 単調DAGで閾値まで進む回数と通過辺の和を直接足して確認する。
        assert(result.first == (unsigned)(limit - start) && result.second == make_pair(limit, sum));
      }
    }
  }
}
