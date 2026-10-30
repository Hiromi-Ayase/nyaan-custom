## トポロジカルソート

`TopologicalSort(g)` は有向グラフの頂点をトポロジカル順に並べた `vector<int>` を返す。各辺 `u -> v` について `u` が `v` より前に現れる。

閉路があれば空の配列を返す。頂点数が 0 の場合も空になる。順序は DFS と隣接リストの順に依存し、辞書順最小ではない。引数は非 const 参照だが、グラフの内容は変更しない。

時間は $O(V+E)$、追加領域は再帰スタックを含め $O(V)$。

#### 実装・検証

- [実装](../../graph/topological-sort.hpp)
- [検証: aoj-grl-4-a.test.cpp](../../verify/verify-aoj-grl/aoj-grl-4-a.test.cpp)
- [検証: aoj-grl-4-b.test.cpp](../../verify/verify-aoj-grl/aoj-grl-4-b.test.cpp)
