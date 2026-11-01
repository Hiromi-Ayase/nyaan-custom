## Dijkstra 法（経路復元用の親付き）

`dijkstra_restore(g, start = 0)` は `vector<vector<pair<int, T>>>`（要素は `(行き先, 重み)`） の各頂点について `(最短距離, 一つ前の頂点)` を返す。

始点は `(0, -1)`、到達不能は `(-1, -1)`。終点が到達可能なことを確認し、親をたどって反転すると始点からの経路を得られる。

優先度付きキューに Radix Heap を使うため、辺重みは非負の整数とする。距離の加算が `T` に収まることも必要。キーのビット数を $B$ とした保守的な時間上界は $O(V+EB)$、追加領域は $O(V+E)$。

#### 実装・検証

- [実装](../../shortest-path/dijkstra-with-restore.hpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
