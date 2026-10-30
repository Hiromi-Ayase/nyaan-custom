## 最小全域有向木

`MinimumCostArborescence(N, root, es)` は、`root` から全頂点に到達できる全域有向木のうち、辺の重みの和が最小のものを求める。

- `es` は `Edges<T>`。有向辺の始点・終点・重みを渡す。
- 成功時は採用した `N-1` 本の辺を返す。コストは返却辺の `cost` を合計する。
- 存在しない場合は空の辺列を返す。`N == 1` の正常な結果も空になる。

各頂点に入る最小辺を選び、閉路を縮約する。Skew Heap と Union Find を使い、時間は償却 $O(E\log(E+1)+V)$、領域は $O(V+E)$。減算を行うので、`T` は負の中間値を扱える型にする。

#### 実装・検証

- [実装](../../graph/minimum-cost-arborescence.hpp)
- [検証: yosupo-directed-mst.test.cpp](../../verify/verify-yosupo-graph/yosupo-directed-mst.test.cpp)
