## 根付き木・逆辺への変換

`rooted_tree(g,root=0)` は BFS で初めて訪れる辺だけを残し、親から子への有向隣接リストを返す。木を渡すと根付き木になる。一般グラフでは到達可能部分の BFS 木となる。

`inverse_tree(g)` はすべての辺の向きを逆にする。`vector<vector<int>>` と `vector<vector<pair<int, T>>>` の両方に対応する。重み付き要素は `(行き先, 重み)`。根付き化・逆辺化のどちらも重みを引き継ぐ。

時間・出力領域 $O(V+E)$。有効な root を渡す。

#### 実装・検証

- [実装](../../tree/convert-tree.hpp)
- [Verify: queries.cpp](../../tests/unit/tree/queries.cpp)
- [Verify: weighted-containers.cpp](../../tests/unit/tree/weighted-containers.cpp)
