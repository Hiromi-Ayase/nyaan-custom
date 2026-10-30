## 最大独立集合

`max_independent_set<m>(g)` は無向グラフの最大独立集合を頂点番号の列で返す。独立集合とは、選んだ頂点間に辺が存在しない集合。

`g` は `vector<vector<int>>`。自己ループのないグラフを渡し、テンプレート引数 `m` は頂点数以上にする。隣接関係は内部で対称化される。返却頂点は番号の昇順。

ビット集合を用いた分岐探索であり、多項式時間のアルゴリズムではない。頂点数を $N$、ビット集合のワード数を $B=\lceil m/64\rceil$ とすると、粗い上界は時間 $O(2^N B)$、領域 $O(NB+N)$。小規模なグラフ向け。

#### 実装・検証

- [実装](../../graph/max-independent-set.hpp)
- [検証: yosupo-max-independent-set.test.cpp](../../verify/verify-yosupo-graph/yosupo-max-independent-set.test.cpp)
