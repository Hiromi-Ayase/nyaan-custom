## 動的 Segment Tree

必要な節点だけを確保し、大きな非負整数座標上の区間積を管理する。

- `DynamicLazySegmentTree<T,E,f,g,h,ti,ei>(n)`: `[0,Rmax)` を管理する。`Rmax` は `n` より大きい最小の 2 冪（最低 2）。各演算・単位元は関数ポインタで指定する。
- `DynamicSegmentTree<T,f,ti>`: 作用を持たない別名。
- `set_val(i,x)`, `get_val(i)`: 一点の代入・取得。未作成の部分は `ti()`。
- `apply(l,r,x)`, `fold(l,r)`: 半開区間の作用・積。範囲内の非空区間を渡す。`apply` に作用の単位元を渡すと assert に失敗する。

`h(old,new)` は古い作用の後に新しい作用を行う合成。区間長は自動で渡されず、未作成節点も `ti()` なので、区間和などでは要素の長さを適切に初期化する必要がある。

各操作は $O(\log Rmax)$。クエリ中の遅延伝播でも節点を確保し、$Q$ 操作後の領域は $O(Q\log Rmax)$。`merge(rhs)` は現状、内部の再帰呼び出し名が不整合でインスタンス化時にコンパイルできない。

#### 実装・検証

- [実装](../../segment-tree/dynamic-segment-tree.hpp)
- [Verify: persistent-and-dynamic.cpp](../../tests/unit/segment-tree/persistent-and-dynamic.cpp)
