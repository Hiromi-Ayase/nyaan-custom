// Verify: graph/dimension-expanded-graph.hpp
// 座標の通し番号・近傍・格子入力と、Dijkstra・到達可能性・連結成分を直接計算で確認する。
#include <bits/stdc++.h>
using namespace std;
#include "graph/dimension-expanded-graph.hpp"

int main() {
  using DG = DimensionExpandedGraph<2>;
  using A = DG::A;
  mt19937 rng(908);
  for (int h = 1; h <= 7; ++h) {
    for (int w = 1; w <= 7; ++w) {
      DG g(h, w);
      g.add(2);
      for (int y = -1; y <= h; ++y) {
        for (int x = -1; x <= w; ++x) {
          A a(y, x);
          // 座標の内外判定と行優先の通し番号を定義どおりに確認する。
          assert(a.ok() == (0 <= y && y < h && 0 <= x && x < w));
          if (!a.ok()) {
            continue;
          }
          assert(a.id() == y * w + x);
          set<pair<int, int>> expected;
          for (int yy = 0; yy < h; ++yy) {
            for (int xx = 0; xx < w; ++xx) {
              if (abs(yy - y) + abs(xx - x) == 1) {
                expected.emplace(yy, xx);
              }
            }
          }
          set<pair<int, int>> actual;
          for (auto b : a.near()) {
            actual.emplace(b[0], b[1]);
          }
          // 近傍は格子内でマンハッタン距離1の座標だけを返す。
          assert(actual == expected);
        }
      }
      // 追加頂点は通常の格子点の後に連続して割り当てられる。
      assert(DG::ad(1).ok() && DG::ad(1).id() == h * w + 1 && !DG::ad(2).ok());
      string flat(h * w, '.');
      for (char& c : flat) {
        if (rng() % 4 == 0) {
          c = '#';
        }
      }
      flat[0] = 'S';
      istringstream input(flat);
      g.scan(input);
      // 格子の読み込み・文字検索・座標による参照を確認する。
      assert(g.get_grid() == vector<char>(flat.begin(), flat.end()));
      assert(g.find('S') == A(0, 0) && !g.find('X').ok());
      vector<vector<long long>> d(h * w, vector<long long>(h * w, 1000000));
      for (int u = 0; u < h * w; ++u) {
        d[u][u] = 0;
        for (int v = 0; v < h * w; ++v) {
          if (abs(u / w - v / w) + abs(u % w - v % w) == 1 && flat[v] != '#') {
            d[u][v] = 1 + v % 5;
          }
        }
      }
      for (int k = 0; k < h * w; ++k) {
        for (int u = 0; u < h * w; ++u) {
          for (int v = 0; v < h * w; ++v) {
            d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
          }
        }
      }
      auto transition = [&](A a, auto add) {
        for (auto b : a.near()) {
          if (g(b) != '#') {
            add(b, 1 + b.id() % 5);
          }
        }
      };
      auto shortest = g.dijkstra(transition, A(0, 0));
      auto reachable = g.bfs(
          [&](A a, auto add) {
            for (auto b : a.near()) {
              if (g(b) != '#') {
                add(b);
              }
            }
          },
          A(0, 0));
      for (int v = 0; v < h * w; ++v) {
        // Dijkstraは三重ループの全点対距離と一致する。bfsは仕様上、到達可能性のみを比較する。
        assert(shortest[v] == (d[0][v] == 1000000 ? -1 : d[0][v]));
        assert((reachable[v] != -1) == (d[0][v] != 1000000));
      }
      g.uf([&](A a, auto unite) {
        for (auto b : a.near()) {
          if (g(a) != '#' && g(b) != '#') {
            unite(a, b);
          }
        }
      });
      for (int u = 0; u < h * w; ++u) {
        int size = 0;
        for (int v = 0; v < h * w; ++v) {
          bool connected = u == v || (flat[u] != '#' && flat[v] != '#' && d[u][v] < 1000000);
          // 障害物を除いた連結成分を、通常の頂点番号で求めた到達性と比較する。
          assert(g.same(A(u / w, u % w), A(v / w, v % w)) == connected);
          size += connected;
        }
        // 併合後のサイズは同じ成分に属する座標の個数になる。
        assert(g.size(A(u / w, u % w)) == size);
      }
    }
  }
  // 0-1 BFSは緩和し直さない実装のため、経路が一意な直線上で重み0/1を確認する。
  DG line(1, 20);
  line.add(0);
  auto d = line.bfs01([](A a, auto add) { add(A(0, a[1] + 1), a[1] % 2); }, A(0, 0));
  for (int x = 0; x < 20; ++x) {
    // x歩進む間に通った重み1の辺の本数に一致する。
    assert(d[x] == x / 2);
  }
}
