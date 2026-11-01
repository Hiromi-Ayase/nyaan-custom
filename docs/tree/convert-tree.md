## 根付き木・逆辺への変換

`rooted_tree(g,root=0)` は BFS で初めて訪れる辺だけを残し、親から子への有向隣接リストを返す。木を渡すと根付き木になる。一般グラフでは到達可能部分の BFS 木となる。

`inverse_tree(g)` はすべての辺の向きを逆にする。要素が int の隣接リストと、`src/to/cost` を持つ重み付き辺に対応する。後者は重みを引き継ぐが、追加の辺属性までは保存しない。

時間・出力領域 $O(V+E)$。有効な root を渡す。

#### 実装・検証

- [実装](../../tree/convert-tree.hpp)
- [Verify: queries.cpp](../../tests/unit/tree/queries.cpp)
