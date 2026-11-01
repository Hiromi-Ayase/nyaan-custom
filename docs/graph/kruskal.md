## Kruskal 法

`kruskal(N, es)` は `N` 頂点の無向グラフの最小全域森の重みの和を返す。連結グラフの場合は最小全域木の重みとなる。

`es` は `vector<tuple<int, int, T>>` 型の辺列で、各要素は `(始点, 終点, 重み)` とする。無向辺は一度だけ登録すればよい。負の重みも扱える。

辺列は重みの昇順に**破壊的にソート**される。採用された辺そのものや、連結性の判定結果は返さない。計算量は $O(E\log E + E\alpha(V))$、Union Find の領域は $O(V)$。

#### 実装・検証

- [実装](../../graph/kruskal.hpp)
- [Verify: spanning-trees.cpp](../../tests/unit/graph/spanning-trees.cpp)
