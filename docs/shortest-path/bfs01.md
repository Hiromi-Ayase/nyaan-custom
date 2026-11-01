## 0-1 BFS

`bfs01(g, start = 0)` は、すべての辺重みが 0 または 1 の `vector<vector<pair<int, T>>>`（要素は `(行き先, 重み)`） について単一始点最短距離を返す。

返り値は長さ `g.size()` の `vector<T>`。始点の距離は 0、到達不能は `-1`。重み 0 の遷移を deque の先頭へ、重み 1 の遷移を末尾へ追加する。一般の非負重みには Dijkstra 法を使用する。

時間は $O(V+E)$、追加領域は $O(V+E)$（重複してキューへ入る頂点を含む）。

#### 実装・検証

- [実装](../../shortest-path/bfs01.hpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
