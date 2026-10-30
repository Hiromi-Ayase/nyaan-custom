## 二重辺連結成分分解

無向グラフから橋を取り除いたときの連結成分を求める。

- `TwoEdgeConnectedComponents<G> tecc(g)`: 構築と分解を行う。
- `tecc[v]`, `tecc.comp[v]`: 頂点 `v` の成分番号。
- `tecc.k`: 成分数。`tecc.groups[i]` は成分 `i` の頂点列。
- `tecc.low`: 分解に用いた `LowLink<G>`。
- `tecc.tree`: 橋で成分を結ぶ隣接リスト。ただし現在の実装は、元の橋 `(u, v)` の `u < v` に対応する向きの一辺だけを格納する。無向の縮約森として使う場合は逆辺を補う。

時間は $O(V+E)$、追加領域は $O(V)$。元のグラフは参照で保持される。

#### 実装・検証

- [実装](../../graph/two-edge-connected-components.hpp)
- [検証: yosupo-two-edge-cc.test.cpp](../../verify/verify-yosupo-graph/yosupo-two-edge-cc.test.cpp)
