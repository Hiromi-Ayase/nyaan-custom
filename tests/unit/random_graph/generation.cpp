// Verify: random_graph/random.hpp
// Verify: random_graph/graph.hpp
// Verify: random_graph/gen.hpp
// 固定シードの再現性、乱数の範囲、生成グラフの辺数・重み・連結性・形状と出力形式を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "random_graph/random.hpp"
#include "random_graph/graph.hpp"
#include "random_graph/gen.hpp"

int main() {
  Random first(123456);
  Random second(123456);
  for (int trial = 0; trial < 1000; ++trial) {
    // 同じseedから作った生成器は同じ操作列に同じ値を返す。
    auto x = first.uniform(-1000, 1000);
    assert(x == second.uniform(-1000, 1000) && -1000 <= x && x <= 1000);
    auto p = first.uniform_pair(-100, 100);
    assert(p == second.uniform_pair(-100, 100) && -100 <= p.first && p.first < p.second &&
           p.second <= 100);
    auto real = first.uniform01();
    assert(real == second.uniform01() && 0 <= real && real <= 1);
    assert(first.uniform_bool() == second.uniform_bool());
    int n = trial % 31;
    auto order = first.perm<int>(n);
    auto same = second.perm<int>(n);
    assert(order == same);
    sort(order.begin(), order.end());
    vector<int> expected(n);
    iota(expected.begin(), expected.end(), 0);
    assert(order == expected);
    auto choice = first.choice(n, -15, 15);
    assert(choice == second.choice(n, -15, 15));
    assert((int)choice.size() == n &&
           set<int>(choice.begin(), choice.end()).size() == choice.size());
    auto word = first.lower_string(n);
    assert(word == second.lower_string(n));
    assert((int)word.size() == n &&
           all_of(word.begin(), word.end(), [](char c) { return 'a' <= c && c <= 'z'; }));
  }
  Graph graph(3, true);
  graph.add_directed_edge(0, 2, -7, 4);
  graph.add_undirected_edge(2, 1, 9, 5);
  auto adjacency = graph.adjacent_list(true);
  // 隣接リストでは始点・終点・重み・外部IDを保存し、無向追加は端点を小さい順に並べる。
  assert(adjacency[0].size() == 1 && adjacency[0][0].v == 2 && adjacency[0][0].w == -7 &&
         adjacency[0][0].idx == 4);
  assert(adjacency[1].size() == 1 && adjacency[1][0].v == 2 && adjacency[1][0].idx == 5);
  assert(graph.adjacent_matrix(true) ==
         vector<vector<long long>>({{0, 0, -7}, {0, 0, 9}, {0, 0, 0}}));
  ostringstream text;
  graph.print(text);
  assert(text.str() == "3 2\n1 3 -7\n2 3 9\n");
  ostringstream edges;
  graph.print_edge(edges, true);
  assert(edges.str() == "0 2 -7\n1 2 9\n");
  ostringstream matrix;
  graph.print_matrix(matrix);
  assert(matrix.str() == "0 0 -7\n0 0 9\n-7 9 0\n");
  UndirectedGraphGenerator generator(42);
  using Method = Graph (UndirectedGraphGenerator::*)(int, bool, W, W);
  vector<Method> methods{
      &UndirectedGraphGenerator::tree,         &UndirectedGraphGenerator::path,
      &UndirectedGraphGenerator::star,         &UndirectedGraphGenerator::perfect,
      &UndirectedGraphGenerator::simple,       &UndirectedGraphGenerator::namori,
      &UndirectedGraphGenerator::simple_sparse};
  for (int n = 3; n <= 30; ++n) {
    for (int type = 0; type < (int)methods.size(); ++type) {
      generator.set_seed(100 + n);
      auto g = (generator.*methods[type])(n, true, -10, 20);
      generator.set_seed(100 + n);
      auto repeat = (generator.*methods[type])(n, true, -10, 20);
      ostringstream a;
      ostringstream b;
      a << g;
      b << repeat;
      // グラフ生成もseedを戻すと辺列まで完全に再現する。
      assert(a.str() == b.str());
      auto list = g.adjacent_list();
      set<pair<int, int>> unique_edges;
      int total = 0;
      int max_degree = 0;
      for (int u = 0; u < n; ++u) {
        max_degree = max(max_degree, (int)list[u].size());
        for (auto e : list[u]) {
          ++total;
          // 自己辺がなく重みが指定範囲に収まる。なもり以外は平行辺もない。
          assert(e.u == u && e.v != u && 0 <= e.v && e.v < n && -10 <= e.w && e.w <= 20);
          if (u < e.v) {
            bool inserted = unique_edges.emplace(u, e.v).second;
            assert(type == 5 || inserted);
          }
        }
      }
      assert(total == 2 * g.edges_size());
      if (type != 5) {
        assert((int)unique_edges.size() == g.edges_size());
      }
      if (type <= 2 || type == 3 || type == 5) {
        vector<bool> seen(n);
        vector<int> q{0};
        seen[0] = true;
        for (int i = 0; i < (int)q.size(); ++i) {
          for (auto e : list[q[i]]) {
            if (!seen[e.v]) {
              seen[e.v] = true;
              q.push_back(e.v);
            }
          }
        }
        // 木・完全グラフ・なもりは生成器の契約どおり連結になる。
        assert(q.size() == (size_t)n);
      }
      if (type <= 2) {
        assert(g.edges_size() == n - 1);
      }
      if (type == 1) {
        assert(max_degree == 2);
      }
      if (type == 2) {
        assert(max_degree == n - 1);
      }
      if (type == 3) {
        assert(g.edges_size() == n * (n - 1) / 2);
      }
      if (type == 5) {
        assert(g.edges_size() == n);
      }
    }
    auto selected = generator.test(n, true);
    // 複数の木生成法から選ぶAPIも、辺数n-1を保つ。
    assert(selected.edges_size() == n - 1);
  }
}
