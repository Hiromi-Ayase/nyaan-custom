## Low Link（関節点・橋）

無向グラフを DFS し、関節点と橋を列挙する。非連結グラフにも対応する。

#### 使い方

- `LowLink<G> low(g)`: 構築時に全頂点を探索する。`g` は頂点番号へ変換できる要素を持つ隣接リスト。
- `low.articulation`: 関節点の頂点番号。
- `low.bridge`: 橋の端点 `(u, v)`。常に `u < v`。
- `low.ord[v]`, `low.low[v]`: DFS の訪問順と、後退辺を用いて到達できる最小の訪問順。

時間は $O(V+E)$、追加領域は $O(V)$。親への辺を一本だけ除外するため、多重辺も扱える。グラフを参照で保持するので、構築後も元のグラフを生存させる。

#### 実装・検証

- [実装](../../graph/lowlink.hpp)
- [Verify: cuts.cpp](../../tests/unit/graph/cuts.cpp)
