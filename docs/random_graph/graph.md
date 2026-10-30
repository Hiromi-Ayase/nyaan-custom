## 生成用グラフの保存・出力

`Graph(n,weighted=false)` は `Edge{u,v,w,idx}` の辺列を保持する。重みは long long。通常の `graph-template.hpp` の型とは別物。

`add_directed_edge` は有向辺、`add_undirected_edge` は端点を昇順にした一辺を保存する。`adjacent_list(directed=false)` / `adjacent_matrix(directed=false)` で隣接構造へ変換できる。行列の辺なしは 0、多重辺は最後の重みになる。

`print(os,origin_0=false)` は頂点数・辺数と辺列、`print_edge` は辺列だけを出力する。既定は頂点番号 1 始まり。隣接リスト化は $O(V+E)$、行列化は $O(V^2+E)$。

#### 実装・検証

- [実装](../../random_graph/graph.hpp)
