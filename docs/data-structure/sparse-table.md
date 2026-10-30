## 静的区間最小値

`SparseTable<T>(v)` を構築し、`query(l,r)` で半開区間 `[l,r)` の最小値を取得する。更新操作はない。

演算は `min` に固定されている。空区間は `numeric_limits<T>::max()/2` を返す。デフォルト構築だけでは問い合わせできない。

前処理・領域は $O(n\log n)$、問い合わせは $O(1)$。

#### 実装・検証

- [実装](../../data-structure/sparse-table.hpp)
- [検証: sparse-table.test.cpp](../../verify/verify-unit-test/sparse-table.test.cpp)
- [検証: yosupo-static-rmq.test.cpp](../../verify/verify-yosupo-ds/yosupo-static-rmq.test.cpp)
