## 強連結成分分解

有向グラフを強連結成分に分解し、成分を縮約した DAG を構築する。

- `StronglyConnectedComponents<G> scc(g)`: 構築時に分解する。
- `scc[v]`: 頂点 `v` の成分番号。
- `scc.belong(i)`: 成分 `i` に属する頂点列への参照。
- `scc.dag`: 縮約後の隣接リスト。成分数は `scc.dag.size()`。

成分番号はトポロジカル順で、成分間の辺 `u -> v` について `scc[u] < scc[v]` となる。`dag` の多重辺は除去しない。時間・追加領域は $O(V+E)$。元のグラフを参照で保持し、探索には再帰を使用する。

#### 実装・検証

- [実装](../../graph/strongly-connected-components.hpp)
- [検証: aoj-grl-3-c.test.cpp](../../verify/verify-aoj-grl/aoj-grl-3-c.test.cpp)
- [検証: yosupo-strongly-connected-components.test.cpp](../../verify/verify-yosupo-graph/yosupo-strongly-connected-components.test.cpp)
