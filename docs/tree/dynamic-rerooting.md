## 動的な木の全方位 DP

`DynamicRerooting<Path,Point,Info,vertex,compress,rake,add_edge,add_vertex>(n,info)` は動的な森を Top Tree で管理する。

`vertex(Info)` は単一頂点、`compress(Path,Path)` は縦の結合、`rake(Point,Point)` は枝の結合、`add_edge(Path)` は枝情報への変換、`add_vertex(Point,Info)` は頂点追加。これらを関数ポインタで渡す。

`add_edge(u,v)` は異なる木の頂点を結ぶ。`del_edge(u,v)` は存在する辺を切る。`set_info/get_info` は頂点情報、`query(u)` は u を根とした木全体、`query_subtree(root,u)` は指定根での u 以下の結果。

常に森を保ち、部分木問い合わせは同じ木の頂点で行う。Splay Tree を用いるため単発操作の最悪時間は対数とは限らない。計算量は expose 時のパス・枝の再構成回数とユーザー演算のコストに依存する。

#### 実装・検証

- [実装](../../tree/dynamic-rerooting.hpp)
- [検証: aoj-grl-5-a-dynamic-rerooting.test.cpp](../../verify/verify-aoj-grl/aoj-grl-5-a-dynamic-rerooting.test.cpp)
- [検証: yosupo-point-set-tree-path-composite-sum-fixed-root-2.test.cpp](../../verify/verify-yosupo-graph/yosupo-point-set-tree-path-composite-sum-fixed-root-2.test.cpp)
- [検証: yosupo-point-set-tree-path-composite-sum.test.cpp](../../verify/verify-yosupo-graph/yosupo-point-set-tree-path-composite-sum.test.cpp)
