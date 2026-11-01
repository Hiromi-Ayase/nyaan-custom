## ダイクストラ法（Skew Heap）

`dijkstra_restore_skew_heap(g, start=0)` は各頂点の `(最短距離, 一つ前の頂点)` を返す。始点は `(0, -1)`、到達不能は `(-1, -1)`。

`g` は `vector<vector<pair<int, T>>>` で、各要素は `(行き先, 重み)`。重みは非負で、距離の加算が `T` に収まることが必要。入力グラフは変更しない。親をたどり、得られた列を反転すると最短路を復元できる。

ヒープには頂点ごとに1ノードを置き、距離が短くなった場合はキーを更新する。通常版・Radix Heap版のDijkstraと同時に include できる。

#### 実装・検証

- [実装](../../shortest-path/dijkstra-skew-heap.hpp)
- [Verify: dijkstra-skew-heap.cpp](../../tests/unit/shortest-path/dijkstra-skew-heap.cpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
