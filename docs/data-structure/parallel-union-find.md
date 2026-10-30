## 二つの区間を対応させる Union Find

`ParallelUnionFind(n)` の `unite(l1,r1,l2,r2)` は、同じ長さの半開区間の対応する要素を一斉に併合する。`unite(i,j)` は一点の併合。`find`, `same`, `size` も使える。

第5引数に `f(x,y)` を渡すと、実際の併合時に吸収先・吸収元の根が通知される。代表番号の列を Rolling Hash で比較するため、結果にはハッシュ衝突の可能性がある。

すでに等しい区間の比較は $O(\log n)$。実際の併合と小さい成分の書き換えを合わせ、$Q$ 回の操作全体で概ね $O((n+Q)\log^2 n)$、領域は $O(n)$。

#### 実装・検証

- [実装](../../data-structure/parallel-union-find.hpp)
- [検証: parallel-union-find.test.cpp](../../verify/verify-unit-test/parallel-union-find.test.cpp)
- [検証: yosupo-range-parallel-unionfind.test.cpp](../../verify/verify-yosupo-ds/yosupo-range-parallel-unionfind.test.cpp)
