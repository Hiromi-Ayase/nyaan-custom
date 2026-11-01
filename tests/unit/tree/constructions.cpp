// Verify: tree/pruefer-code.hpp
// Verify: tree/cartesian-tree.hpp
// Verify: tree/inclusion-tree.hpp
// Verify: tree/process-of-merging-tree.hpp
// 最小葉の除去によるPruefer符号化、区間最小値によるCartesian Tree、包含・併合の全探索を使う。
#include <bits/stdc++.h>
using namespace std;
#include "graph/graph-template.hpp"
#include "data-structure/union-find.hpp"
#include "tree/pruefer-code.hpp"
#include "tree/cartesian-tree.hpp"
#include "tree/inclusion-tree.hpp"
#include "tree/process-of-merging-tree.hpp"

int main() {
  mt19937 rng(1003);
  for (int n = 3; n <= 7; ++n) {
    int total = 1;
    for (int i = 0; i < n - 2; ++i) {
      total *= n;
    }
    for (int mask = 0; mask < total; ++mask) {
      vector<int> code(n - 2);
      int value = mask;
      for (int& x : code) {
        x = value % n;
        value /= n;
      }
      auto g = pruefer_code(code);
      vector<int> degree(n);
      for (int u = 0; u < n; ++u) {
        degree[u] = g[u].size();
      }
      vector<int> encoded;
      for (int i = 0; i < n - 2; ++i) {
        int leaf = 0;
        while (degree[leaf] != 1) {
          ++leaf;
        }
        int neighbor = -1;
        for (int v : g[leaf]) {
          if (degree[v] > 0) {
            neighbor = v;
          }
        }
        // 最小葉は残っている隣接頂点をちょうど1つ持つ。
        assert(neighbor != -1);
        encoded.push_back(neighbor);
        --degree[leaf];
        --degree[neighbor];
      }
      // 全符号を復号してから定義どおりに最小葉を取り除くと、元の符号に戻る。
      assert(encoded == code);
    }
  }
  for (int n = 0; n <= 50; ++n) {
    for (int trial = 0; trial < 30; ++trial) {
      vector<int> a(n);
      for (int& x : a) {
        x = (int)(rng() % 9) - 4;
      }
      auto [tree, root] = CartesianTree(a);
      vector<vector<int>> expected(n);
      auto build = [&](auto&& self, int l, int r) -> int {
        if (l == r) {
          return -1;
        }
        int smallest = min_element(a.begin() + l, a.begin() + r) - a.begin();
        int left = self(self, l, smallest);
        int right = self(self, smallest + 1, r);
        if (left != -1) {
          expected[smallest].push_back(left);
        }
        if (right != -1) {
          expected[smallest].push_back(right);
        }
        return smallest;
      };
      int expected_root = build(build, 0, n);
      // 同値なら左端の最小値を根に選び、左右区間を再帰する素朴な構築と一致する。
      assert(root == expected_root && tree == expected);
    }
  }
  for (int trial = 0; trial < 200; ++trial) {
    int n = 1 + rng() % 50;
    vector<pair<int, int>> intervals;
    auto divide = [&](auto&& self, int l, int r) -> void {
      intervals.emplace_back(l, r);
      if (rng() % 4 == 0) {
        intervals.emplace_back(l, r);
      }
      if (r - l <= 1) {
        return;
      }
      int mid = l + 1 + rng() % (r - l - 1);
      self(self, l, mid);
      self(self, mid, r);
    };
    divide(divide, 0, n);
    shuffle(intervals.begin(), intervals.end(), rng);
    auto tree = inclusion_tree(intervals, n);
    vector<vector<int>> expected(intervals.size());
    for (int i = 1; i < (int)intervals.size(); ++i) {
      int p = i - 1;
      while (!(intervals[p].first <= intervals[i].first &&
               intervals[i].second <= intervals[p].second)) {
        --p;
      }
      expected[p].push_back(i);
    }
    // 最後に現れる包含区間を総当たりで選んだ親と一致し、同一区間も連鎖する。
    assert(tree == expected);
    assert(intervals.front() == make_pair(-1, n + 1));
  }
  for (int n = 1; n <= 30; ++n) {
    Edges<int> edges;
    for (int u = 1; u < n; ++u) {
      edges.emplace_back(u, rng() % u, rng() % 30);
    }
    for (int i = 0; i < n; ++i) {
      edges.emplace_back(rng() % n, rng() % n, rng() % 30);
    }
    shuffle(edges.begin(), edges.end(), rng);
    auto [tree, weights, root] = process_of_merging_tree(edges);
    vector<set<int>> cluster(2 * n - 1);
    for (int u = 0; u < n; ++u) {
      cluster[u].insert(u);
    }
    vector<int> component(n);
    iota(component.begin(), component.end(), 0);
    int next = n;
    for (auto e : edges) {
      int a = component[e.src];
      int b = component[e.to];
      if (a == b) {
        continue;
      }
      set<int> wanted = cluster[a];
      wanted.insert(cluster[b].begin(), cluster[b].end());
      set<int> actual;
      for (auto child : tree[next]) {
        actual.insert(cluster[child.to].begin(), cluster[child.to].end());
        // 補助頂点からの辺は、この併合に使った重みを保持する。
        assert(child.cost == e.cost);
      }
      // 入力順に集合を併合した結果と、補助頂点の子が表す集合が一致する。
      assert(actual == wanted && weights[next - n] == e.cost && tree[next].size() == 2);
      cluster[next] = wanted;
      for (int& x : component) {
        if (x == a || x == b) {
          x = next;
        }
      }
      ++next;
    }
    // 全元頂点が根の下に集まり、余分な補助頂点がない。
    assert(root == 2 * n - 2 && next == 2 * n - 1 && (int)cluster[root].size() == n);
  }
}
