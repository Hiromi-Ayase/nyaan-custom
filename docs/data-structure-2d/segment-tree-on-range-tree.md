## Segment Tree を用いた領域木

`RangeTree<S,T,op,e>` は二次元点の値を管理する。`S` は座標型、`T` は値型。結合演算 `T op(T,T)` と単位元 `T e()` をテンプレート引数に指定し、デフォルト構築する。内部の木には AtCoder Library のセグメント木を使う。

`add_point(x,y)` で全更新点を登録し、`build()` を一度呼ぶ。`add(x,y,a)` は登録点へ `+= a`、`sum(xl,yl,xr,yr)` は半開矩形の集約を返す。

点の追加は構築前に済ませる。`op` を指定できるが一点更新は加算に固定されているので、和など整合する演算を選ぶ。二次元の分割順に依存しない集約が必要。

前処理・領域は $O(n\log n)$、更新・取得は $O(\log^2 n)$。抽象版の `RangeTree` と同時に include しない。

#### 実装・検証

- [実装](../../data-structure-2d/segment-tree-on-range-tree.hpp)
- [検証: yosupo-point-add-rectangle-sum-dseg2d.test.cpp](../../verify/verify-yosupo-ds/yosupo-point-add-rectangle-sum-dseg2d.test.cpp)
- [検証: ACL 移行・矩形和の差分検証](../../verify/verify-unit-test/acl-segment-tree.test.cpp)
