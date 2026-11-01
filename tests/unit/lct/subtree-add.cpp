// Verify: lct/link-cut-tree-subtree-add.hpp
// 部分木加算を各子孫へ直接適用し、link/cutと根変更の後も遅延作用が正しい範囲に残るか確認する。
#include <bits/stdc++.h>
using namespace std;
#include "lct/link-cut-tree-subtree-add.hpp"

long long add(long long a, long long b) {
  return a + b;
}

long long subtract(long long a, long long b) {
  return a - b;
}

long long multiply(long long a, long long b) {
  return a * b;
}

int main() {
  mt19937 rng(2003);
  for (int n = 1; n <= 25; ++n) {
    using Tree = LinkCutTreeSubtreeQuery<long long, add, subtract, multiply>;
    Tree tree;
    vector<Tree::Ptr> nodes;
    vector<long long> values(n);
    for (int i = 0; i < n; ++i) {
      values[i] = (int)(rng() % 21) - 10;
      nodes.push_back(new Tree::Node(values[i]));
    }
    vector<vector<bool>> graph(n, vector<bool>(n));
    auto parents = [&](int root) {
      vector<int> parent(n, -2);
      parent[root] = -1;
      vector<int> q{root};
      for (int i = 0; i < (int)q.size(); ++i) {
        for (int v = 0; v < n; ++v) {
          if (graph[q[i]][v] && parent[v] == -2) {
            parent[v] = q[i];
            q.push_back(v);
          }
        }
      }
      return parent;
    };
    for (int step = 0; step < 1500; ++step) {
      int u = rng() % n;
      int v = rng() % n;
      auto parent = parents(u);
      if (step % 3 == 0 && u != v) {
        if (graph[u][v]) {
          tree.cut(nodes[u], nodes[v]);
          graph[u][v] = false;
          graph[v][u] = false;
        } else if (parent[v] == -2) {
          tree.link(nodes[u], nodes[v]);
          graph[u][v] = true;
          graph[v][u] = true;
        }
      } else if (step % 3 == 1) {
        values[u] = (int)(rng() % 101) - 50;
        tree.set_key(nodes[u], values[u]);
      }
      parent = parents(u);
      if (parent[v] == -2) {
        continue;
      }
      vector<int> subtree;
      for (int x = 0; x < n; ++x) {
        if (parent[x] == -2) {
          continue;
        }
        int ancestor = x;
        while (ancestor != -1 && ancestor != v) {
          ancestor = parent[ancestor];
        }
        if (ancestor == v) {
          subtree.push_back(x);
        }
      }
      tree.evert(nodes[u]);

      if (step % 3 == 2) {
        long long delta = (int)(rng() % 21) - 10;
        tree.subtree_add(nodes[v], delta);
        for (int x : subtree) {
          values[x] += delta;
        }
      }

      long long expected = 0;
      for (int x : subtree) {
        expected += values[x];
      }
      // 指定した根から親鎖をたどって判定した子孫だけの和を比較する。
      assert(tree.subtree_sum(nodes[v]) == expected);
      assert(tree.get_root(nodes[v]) == nodes[u]);
      // 部分木更新の後でも一点の値がvectorの期待値と一致する。
      assert(tree.get_key(nodes[v]) == values[v]);
    }
    for (auto node : nodes) {
      delete node;
    }
  }
}
