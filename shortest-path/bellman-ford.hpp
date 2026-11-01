#pragma once

#include <limits>
#include <tuple>
#include <vector>
using namespace std;

// bellman-ford法
// goalが存在しないとき-> 負閉路が存在するときは空列を返す
// goalが存在するとき  -> startとgoalの間に負閉路が存在する時に負閉路を返す
template <typename T>
vector<T> bellman_ford(int N, const vector<tuple<int, int, T>>& es, int start = 0, int goal = -1) {
  T INF = numeric_limits<T>::max() / 2;
  vector<T> d(N, INF);
  d[start] = 0;
  for (int i = 0; i < N; i++) {
    bool update = false;
    for (const auto& [src, to, cost] : es) {
      if (d[src] == INF) {
        continue;
      }
      if (d[to] > d[src] + cost) {
        update = true;
        d[to] = d[src] + cost;
      }
    }
    if (!update) {
      return d;
    }
  }

  if (goal == -1) {
    return vector<T>();
  }
  vector<bool> negative(N, false);
  for (int i = 0; i < N; i++) {
    for (const auto& [src, to, cost] : es) {
      if (d[src] == INF) {
        continue;
      }
      if (d[to] > d[src] + cost) {
        negative[to] = true;
        d[to] = d[src] + cost;
      }
      if (negative[src] == true) {
        negative[to] = true;
      }
    }
  }

  if (negative[goal] == true) {
    return vector<T>();
  } else {
    return d;
  }
}

/**
 * @docs docs/shortest-path/bellman-ford.md
 */
