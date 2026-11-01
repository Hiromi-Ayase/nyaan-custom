## ダイクストラ法（Radix Heapを使う別実装）

グラフ引数は `const vector<vector<pair<int, T>>>&`。`g[u]` に `(行き先, 重み)` を格納する。辺重みは非負の整数で、距離の加算が `T` に収まることが必要。

- `dijkstra_fast(g, start=0)`: 各頂点への最短距離を `vector<T>` で返す。到達不能は `-1`。
- `dijkstra_point(g, start, goal)`: 指定した終点への最短距離だけを返す。到達不能は `-1`、始点と終点が同じ場合は0。
- `dijkstra_restore_fast(g, start=0)`: 各頂点の `(距離, 一つ前の頂点)` を返す。始点は `(0, -1)`、到達不能は `(-1, -1)`。

通常版の `dijkstra` / `dijkstra_restore` とは関数名を分けているため、同時に include できる。入力グラフは変更しない。キーのビット数を $B$ とすると時間の上界は $O(V+EB)$、追加領域は $O(V+E)$。

#### 実装・検証

- [実装](../../shortest-path/dijkstra-fast.hpp)
- [Verify: dijkstra-fast.cpp](../../tests/unit/shortest-path/dijkstra-fast.cpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
