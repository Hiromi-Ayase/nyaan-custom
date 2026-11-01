## 二重頂点連結成分分解

無向グラフを二重頂点連結成分に分解する。各成分を辺の集合として保持し、関節点は複数の成分に含まれ得る。

- `BiConnectedComponents<G> bcc(g)`: 構築時に分解する。
- `bcc.bc[i]`: 成分 `i` の辺の列。端点は `(min(u,v), max(u,v))`。
- `LowLink<G>` を継承しており、`articulation`, `bridge`, `ord`, `low` も参照できる。

橋は一辺だけの成分となる。孤立点は `bc` に現れない。この実装の成分列挙は親への全辺を除外するので、自己ループ・多重辺のない無向グラフを入力する。`build()` はコンストラクタが呼ぶため、重ねて呼ばない。

時間・追加領域は $O(V+E)$。

#### 実装・検証

- [実装](../../graph/biconnected-components.hpp)
- [Verify: cuts.cpp](../../tests/unit/graph/cuts.cpp)
