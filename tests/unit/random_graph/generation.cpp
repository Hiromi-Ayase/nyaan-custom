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
  vector<vector<pair<int, long long>>> directed(3);
  directed[0].emplace_back(2, -7);
  directed[1].emplace_back(2, 9);
  // 標準のpair隣接リストから、向きと重みを保って辺列・行列に変換できる。
  assert((random_graph::edge_list(directed, true) ==
          vector<tuple<int, int, long long>>({{0, 2, -7}, {1, 2, 9}})));
  assert(random_graph::adjacent_matrix(directed) ==
         vector<vector<long long>>({{0, 0, -7}, {0, 0, 9}, {0, 0, 0}}));
  ostringstream text;
  random_graph::print(text, directed, true, true);
  assert(text.str() == "3 2\n1 3 -7\n2 3 9\n");
  ostringstream edges;
  random_graph::print_edges(edges, directed, true, true, true);
  assert(edges.str() == "0 2 -7\n1 2 9\n");
  auto undirected_graph = directed;
  undirected_graph[2].emplace_back(0, -7);
  undirected_graph[2].emplace_back(1, 9);
  ostringstream matrix;
  random_graph::print_matrix(matrix, undirected_graph);
  assert(matrix.str() == "0 0 -7\n0 0 9\n-7 9 0\n");
  undirected_graph[2].emplace_back(2, 13);
  undirected_graph[2].emplace_back(2, 13);
  // 無向自己ループは隣接リスト内の2要素を、辺列では1本に戻す。
  assert(random_graph::edge_count(undirected_graph) == 3);
  assert(random_graph::edge_list(undirected_graph).back() == make_tuple(2, 2, 13LL));

  vector<vector<pair<int, long long>>> repeated(2);
  repeated[0] = {{0, 13}, {1, 5}, {0, 17}, {1, 5}, {0, 13}, {0, 17}, {0, 13}, {0, 13}};
  repeated[1] = {{0, 5}, {0, 5}};
  auto actual_edges = random_graph::edge_list(repeated);
  multiset<tuple<int, int, long long>> expected_edges{
      {0, 0, 13}, {0, 0, 13}, {0, 0, 17}, {0, 1, 5}, {0, 1, 5}};
  // 離れて格納された自己ループも重みごとに組にし、多重辺の本数を保つ。
  assert((multiset<tuple<int, int, long long>>(actual_edges.begin(), actual_edges.end()) ==
          expected_edges));
  assert(random_graph::edge_count(repeated) == 5);
  // 有向指定では自己ループや逆向きの要素もそれぞれ1本として数える。
  assert(random_graph::edge_list(repeated, true).size() == 10);
  assert(random_graph::edge_count(repeated, true) == 10);
  assert(random_graph::adjacent_matrix(repeated) == vector<vector<long long>>({{13, 5}, {5, 0}}));
  vector<vector<pair<int, long long>>> empty;
  ostringstream empty_text;
  random_graph::print(empty_text, empty);
  // 頂点も辺もないグラフは、空の辺列と行列、ヘッダ1行だけを返す。
  assert(random_graph::edge_list(empty).empty());
  assert(random_graph::adjacent_matrix(empty).empty());
  assert(empty_text.str() == "0 0\n");

  UndirectedGraphGenerator generator(42);
  using Method = vector<vector<pair<int, long long>>> (UndirectedGraphGenerator::*)(
      int, bool, long long, long long);
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
      random_graph::print(a, g, true);
      random_graph::print(b, repeat, true);
      // グラフ生成もseedを戻すと辺列まで完全に再現する。
      assert(a.str() == b.str());
      const auto& list = g;
      set<pair<int, int>> unique_edges;
      int total = 0;
      int max_degree = 0;
      for (int u = 0; u < n; ++u) {
        max_degree = max(max_degree, (int)list[u].size());
        for (auto [v, weight] : list[u]) {
          ++total;
          // 自己辺がなく重みが指定範囲に収まる。なもり以外は平行辺もない。
          assert(v != u && 0 <= v && v < n && -10 <= weight && weight <= 20);
          // 無向辺は、同じ重みの逆辺を同じ本数だけ持つ。
          assert(count(list[u].begin(), list[u].end(), make_pair(v, weight)) ==
                 count(list[v].begin(), list[v].end(), make_pair(u, weight)));
          if (u < v) {
            bool inserted = unique_edges.emplace(u, v).second;
            assert(type == 5 || inserted);
          }
        }
      }
      assert(total == 2 * random_graph::edge_count(g));
      if (type != 5) {
        assert((int)unique_edges.size() == random_graph::edge_count(g));
      }
      if (type <= 2 || type == 3 || type == 5) {
        vector<bool> seen(n);
        vector<int> q{0};
        seen[0] = true;
        for (int i = 0; i < (int)q.size(); ++i) {
          for (auto [v, weight] : list[q[i]]) {
            if (!seen[v]) {
              seen[v] = true;
              q.push_back(v);
            }
          }
        }
        // 木・完全グラフ・なもりは生成器の契約どおり連結になる。
        assert(q.size() == (size_t)n);
      }
      if (type <= 2) {
        assert(random_graph::edge_count(g) == n - 1);
      }
      if (type == 1) {
        assert(max_degree == 2);
      }
      if (type == 2) {
        assert(max_degree == n - 1);
      }
      if (type == 3) {
        assert(random_graph::edge_count(g) == n * (n - 1) / 2);
      }
      if (type == 5) {
        assert(random_graph::edge_count(g) == n);
      }
    }
    auto selected = generator.test(n, true);
    // 複数の木生成法から選ぶAPIも、辺数n-1を保つ。
    assert(random_graph::edge_count(selected) == n - 1);
    for (const auto& neighbors : selected) {
      for (auto [v, weight] : neighbors) {
        // 重みなし指定の生成結果もpair形式で、重みは一律1になる。
        assert(weight == 1);
      }
    }
  }
}
