## 根付き木のハッシュ

`RootedTreeHash<G>(g,root=0)` は子の順序に依存しない根付き部分木ハッシュを計算する。`hash[v]` は v 以下の形、`depth[v]` は根からの距離ではなく部分木の高さ。

非空の無向木を渡す。頂点ラベル・辺重みはハッシュに含めない。同じ G 型では高さごとの乱数を共有するので、その範囲で比較できる。異なる形でもハッシュ衝突の可能性がある。

再帰 DFS により時間・領域 $O(n)$。元のグラフは参照で保持される。

#### 実装・検証

- [実装](../../tree/rooted-tree-hash.hpp)
- [検証: aoj-1613.test.cpp](../../verify/verify-aoj-other/aoj-1613.test.cpp)
- [検証: yosupo-tree-hash.test.cpp](../../verify/verify-yosupo-graph/yosupo-tree-hash.test.cpp)
- [検証: yuki-1789.test.cpp](../../verify/verify-yuki/yuki-1789.test.cpp)
