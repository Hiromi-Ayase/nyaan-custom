// Verify: tree/dynamic-rerooting.hpp
// 小さな森でlink/cut・頂点重み更新を繰り返し、全体と部分木の重み・距離和を毎回BFSで求める。
#include <bits/stdc++.h>
using namespace std;
#include "tree/dynamic-rerooting.hpp"

struct Path {
  long long length;
  long long sum;
  long long top;
  long long bottom;
};

struct Point {
  long long sum;
  long long distance;
};

Path vertex(const long long& weight) {
  return {1, weight, 0, 0};
}

Path compress(const Path& a, const Path& b) {
  return {a.length + b.length, a.sum + b.sum, a.top + b.top + a.length * b.sum,
          b.bottom + a.bottom + b.length * a.sum};
}

Point rake(const Point& a, const Point& b) {
  return {a.sum + b.sum, a.distance + b.distance};
}

Point add_edge(const Path& a) {
  return {a.sum, a.top + a.sum};
}

Path add_vertex(const Point& a, const long long& weight) {
  return {1, a.sum + weight, a.distance, a.distance};
}

int main() {
  mt19937 rng(1007);
  for (int n = 1; n <= 30; ++n) {
    vector<long long> weights(n);
    vector<vector<bool>> graph(n, vector<bool>(n));
    DynamicRerooting<Path, Point, long long, vertex, compress, rake, add_edge, add_vertex> solver(
        n, weights);
    auto bfs = [&](int source, int blocked) {
      vector<int> distance(n, -1);
      vector<int> q{source};
      distance[source] = 0;
      for (int i = 0; i < (int)q.size(); ++i) {
        for (int v = 0; v < n; ++v) {
          if (v != blocked && graph[q[i]][v] && distance[v] == -1) {
            distance[v] = distance[q[i]] + 1;
            q.push_back(v);
          }
        }
      }
      return distance;
    };
    for (int step = 0; step < 400; ++step) {
      int u = rng() % n;
      int v = rng() % n;
      auto distance = bfs(u, -1);
      if (step % 3 == 0 && u != v) {
        if (graph[u][v]) {
          solver.del_edge(u, v);
          graph[u][v] = false;
          graph[v][u] = false;
        } else if (distance[v] == -1) {
          solver.add_edge(u, v);
          graph[u][v] = true;
          graph[v][u] = true;
        }
      } else {
        weights[u] = (int)(rng() % 101) - 50;
        solver.set_info(u, weights[u]);
        // 更新した頂点情報をそのまま取り出せる。
        assert(solver.get_info(u) == weights[u]);
      }
      distance = bfs(u, -1);
      long long sum = 0;
      long long weighted_distance = 0;
      for (int i = 0; i < n; ++i) {
        if (distance[i] != -1) {
          sum += weights[i];
          weighted_distance += weights[i] * distance[i];
        }
      }
      auto result = solver.query(u);
      // 根uからの距離を全探索し、成分の重み和と距離重み和の両方を確認する。
      assert(result.sum == sum && result.top == weighted_distance);
      if (distance[v] != -1) {
        int parent = -1;
        for (int i = 0; i < n; ++i) {
          if (graph[v][i] && distance[i] + 1 == distance[v]) {
            parent = i;
          }
        }
        auto subtree = bfs(v, parent);
        sum = 0;
        weighted_distance = 0;
        for (int i = 0; i < n; ++i) {
          if (subtree[i] != -1) {
            sum += weights[i];
            weighted_distance += weights[i] * subtree[i];
          }
        }
        result = solver.query_subtree(u, v);
        // uを根とするvの部分木は、vから親への辺を除いた連結成分に一致する。
        assert(result.sum == sum && result.top == weighted_distance);
      }
    }
  }
}
