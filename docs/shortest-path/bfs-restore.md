## 幅優先探索（経路復元用の親付き）

`bfs_restore(g, st = 0)` は重みなしグラフを BFS し、各頂点の `(距離, 一つ前の頂点)` を返す。`g` は `vector<vector<int>>`。

始点は `(0, -1)`、到達不能は `(-1, -1)`。到達可能な終点から親をたどり、列を反転すると経路を復元できる。距離は辺数で、重み付きグラフには使用しない。

時間は $O(V+E)$、領域は $O(V)$。このヘッダは標準ヘッダを include しないため、`vector`, `pair`, `queue` と `std` の名前を先に利用可能にする。

#### 実装・検証

- [実装](../../shortest-path/bfs-restore.hpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
