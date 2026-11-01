// Verify: lct/link-cut-base.hpp
// Verify: lct/link-cut-tree.hpp
// Verify: lct/link-cut-tree-lazy.hpp
// 森を隣接行列で保持し、BFSの経路・親・LCA・祖先と動的木の値を比較する。
#include <bits/stdc++.h>
using namespace std;
#include "lct/link-cut-base.hpp"
#include "lct/link-cut-tree.hpp"
#include "lct/link-cut-tree-lazy.hpp"

string join(string a, string b) {
  return a + b;
}

string reverse_value(string a) {
  reverse(a.begin(), a.end());
  return a;
}

string paint(string a, char c) {
  return c ? string(a.size(), c) : a;
}

char compose(char old, char newer) {
  return newer ? newer : old;
}

int main() {
  mt19937 rng(2002);
  for (int n = 1; n <= 25; ++n) {
    LinkCutTree<string, join, reverse_value> plain;
    LazyLinkCutTree<string, char, join, paint, compose, reverse_value> lazy;
    vector<decltype(plain)::Ptr> pv;
    vector<decltype(lazy)::Ptr> lv;
    vector<string> values(n);
    for (int i = 0; i < n; ++i) {
      values[i] = string(1, 'a' + i % 26);
      pv.push_back(plain.my_new(values[i]));
      lv.push_back(lazy.my_new(values[i]));
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
      if (step % 4 == 0 && u != v) {
        if (graph[u][v]) {
          plain.cut(pv[u], pv[v]);
          lazy.cut(lv[u], lv[v]);
          graph[u][v] = false;
          graph[v][u] = false;
        } else if (parent[v] == -2) {
          plain.link(pv[u], pv[v]);
          lazy.link(lv[u], lv[v]);
          graph[u][v] = true;
          graph[v][u] = true;
        }
      } else if (step % 4 == 1) {
        values[u] = string(1, 'a' + rng() % 26);
        plain.set_key(pv[u], values[u]);
        lazy.set_key(lv[u], values[u]);
      }
      parent = parents(u);
      if (parent[v] == -2) {
        // 異なる連結成分の頂点間にはLCAが存在しない。
        assert(plain.lca(pv[u], pv[v]) == nullptr && lazy.lca(lv[u], lv[v]) == nullptr);
        continue;
      }
      vector<int> path;
      for (int x = v; x != -1; x = parent[x]) {
        path.push_back(x);
      }
      reverse(path.begin(), path.end());
      if (step % 4 == 2) {
        char c = 'a' + rng() % 26;
        lazy.apply(lv[u], lv[v], c);
        for (int x : path) {
          values[x] = string(1, c);
          plain.set_key(pv[x], values[x]);
        }
      }
      string expected;
      for (int x : path) {
        expected += values[x];
      }
      // パス集約は頂点集合だけでなく、uからvへの文字列順序まで一致する。
      assert(plain.fold(pv[u], pv[v]) == expected && lazy.fold(lv[u], lv[v]) == expected);
      plain.evert(pv[u]);
      lazy.evert(lv[u]);
      for (int x = 0; x < n; ++x) {
        if (parent[x] == -2) {
          continue;
        }
        // 根の変更後の親を、同じ根からのBFSで求めた親と比較する。
        assert(plain.get_root(pv[x]) == pv[u] && lazy.get_root(lv[x]) == lv[u]);
        assert(plain.get_parent(pv[x]) == (parent[x] == -1 ? nullptr : pv[parent[x]]));
        assert(lazy.get_parent(lv[x]) == (parent[x] == -1 ? nullptr : lv[parent[x]]));
      }
      for (int k = 0; k <= (int)path.size(); ++k) {
        // get_kthはvから根方向の順序で、経路長を超えればnullptrを返す。
        auto a = k == (int)path.size() ? nullptr : pv[path[path.size() - 1 - k]];
        auto b = k == (int)path.size() ? nullptr : lv[path[path.size() - 1 - k]];
        assert(plain.get_kth(pv[v], k) == a && lazy.get_kth(lv[v], k) == b);
      }
      int other = rng() % n;
      if (parent[other] != -2) {
        set<int> ancestors;
        for (int x = v; x != -1; x = parent[x]) {
          ancestors.insert(x);
        }
        int common = other;
        while (!ancestors.count(common)) {
          common = parent[common];
        }
        // LCAは親鎖の最初の共通頂点に一致する。
        assert(plain.lca(pv[v], pv[other]) == pv[common] &&
               lazy.lca(lv[v], lv[other]) == lv[common]);
      }
      // 一点取得は遅延されたパス代入を反映する（lazy版は根を変更するので最後に行う）。
      assert(plain.get_key(pv[v]) == values[v] && lazy.get_key(lv[v]) == values[v]);
    }
    for (auto p : pv) {
      delete p;
    }
    for (auto p : lv) {
      delete p;
    }
  }
}
