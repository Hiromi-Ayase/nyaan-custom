## 抽象化した領域木

`RangeTree<DS,S,T>(nw,ad,sm,mrg,ti)` は内側の一次元データ構造を差し替えられる二次元領域木。

`nw(size)` は `DS*` を生成、`ad(ds,index,value)` は一点更新、`sm(ds,l,r)` は半開区間の集約、`mrg(a,b)` は結果の結合を行う。`ti` は単位元。

`add_point(x,y)` で全更新点を登録し、`build()` を一度実行する。その後 `add(x,y,value)` と `sum(xl,yl,xr,yr)`（半開矩形）を使う。更新先を後から新設することはできない。矩形全体の集約には順序に依存しない演算を用いる。

外側の操作は $O(\log n)$ 個の一次元構造を訪れる。内側が Segment Tree なら更新・取得 $O(\log^2 n)$、領域 $O(n\log n)$。`segment-tree-on-range-tree.hpp` の `RangeTree` と名前が衝突する。

#### 実装・検証

- [実装](../../data-structure-2d/abstract-range-tree.hpp)
- [検証: yosupo-point-add-rectangle-sum-abstruct-range-tree.test.cpp](../../verify/verify-yosupo-ds/yosupo-point-add-rectangle-sum-abstruct-range-tree.test.cpp)
