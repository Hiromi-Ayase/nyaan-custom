// Verify: tree/tree-hash.hpp
// Verify: tree/rooted-tree-hash.hpp
// 子の括弧列表現をソートした完全な同型判定とハッシュを比較し、頂点番号の置換も試す。
#include <bits/stdc++.h>
using namespace std;
#include "tree/tree-hash.hpp"
#include "tree/rooted-tree-hash.hpp"

string canonical(const vector<vector<int>>& g, int u, int parent) {
  vector<string> children;
  for (int v : g[u]) {
    if (v != parent) {
      children.push_back(canonical(g, v, u));
    }
  }
  sort(children.begin(), children.end());
  string result = "(";
  for (auto& s : children) {
    result += s;
  }
  return result + ")";
}

int main() {
  using Graph = vector<vector<int>>;
  using H = RootedTreeHash<Graph>;
  H::xs().clear();
  for (int i = 0; i <= 40; ++i) {
    H::xs().push_back(H::Hash::set(100003 + 7919LL * i));
  }
  mt19937 rng(1004);
  map<string, vector<H::Hash>> known;
  for (int n = 1; n <= 30; ++n) {
    for (int trial = 0; trial < 50; ++trial) {
      Graph g(n);
      for (int u = 1; u < n; ++u) {
        int p = rng() % u;
        g[u].push_back(p);
        g[p].push_back(u);
      }
      vector<int> permutation(n);
      iota(permutation.begin(), permutation.end(), 0);
      shuffle(permutation.begin(), permutation.end(), rng);
      Graph changed(n);
      for (int u = 0; u < n; ++u) {
        for (int v : g[u]) {
          changed[permutation[u]].push_back(permutation[v]);
        }
      }
      string unrooted;
      map<string, H::Hash> rooted;
      for (int root = 0; root < n; ++root) {
        string shape = canonical(g, root, -1);
        if (unrooted.empty() || shape < unrooted) {
          unrooted = shape;
        }
        H original(g, root);
        H renamed(changed, permutation[root]);
        // 頂点番号と隣接順を変えても、同じ根付き木のハッシュは変わらない。
        assert(original.hash[root] == renamed.hash[permutation[root]]);
        for (auto& [other, hash] : rooted) {
          // この小規模集合では、括弧列による厳密な同型判定と一致する。
          assert((other == shape) == (hash == original.hash[root]));
        }
        rooted[shape] = original.hash[root];
      }
      auto hash = tree_hash(g);
      // 根なしのハッシュも頂点の置換で不変になる。
      assert(hash == tree_hash(changed));
      for (auto& [shape, value] : known) {
        // 根を全て試した最小括弧列が、根なし木の同型判定の独立な期待値になる。
        assert((shape == unrooted) == (value == hash));
      }
      known[unrooted] = hash;
    }
  }
}
