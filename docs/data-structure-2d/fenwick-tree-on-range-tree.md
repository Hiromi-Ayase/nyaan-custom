## Fenwick Tree を用いた領域木

`FenwickRangeTree<S,T>` に `add_point(x,y)` で全更新点を登録し、`build()` を一度呼ぶ。

`add(x,y,a)` は登録点への加算、`sum(x,y)` は両座標がそれぞれ `x,y` 未満の点の和、`sum(xl,yl,xr,yr)` は半開矩形の和。`T` には零・加算・減算が必要。構築後に新しい点は登録できない。

前処理は保守的に $O(n\log^2 n)$、領域は $O(n\log n)$、更新・取得は $O(\log^2 n)$。

#### 実装・検証

- [実装](../../data-structure-2d/fenwick-tree-on-range-tree.hpp)
- [検証: yosupo-point-add-rectangle-sum-rtree-fenwick.test.cpp](../../verify/verify-yosupo-ds/yosupo-point-add-rectangle-sum-rtree-fenwick.test.cpp)
