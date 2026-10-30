## 最大・最小連続部分列和のモノイド

`MaxInterval<T>` は区間和と、空でない連続部分列の最大・最小和をまとめて管理する。

- `MaxInterval()` は空区間の単位元、`MaxInterval(x)` は一要素、`MaxInterval(x,n)` は `x` が `n` 個並ぶ区間。
- `sum`, `num`: 全体の和と長さ。
- `max`, `lmax`, `rmax`: 部分列・接頭辞・接尾辞の最大和。`min`, `lmin`, `rmin` は対応する最小和。
- `merge(a,b)`: 左区間 `a` と右区間 `b` の連結を $O(1)$ で計算する。順序を保って結合する。

Segment Tree の要素・結合演算として利用できる。区間代入は `MaxInterval(x, old.num)` を作ればよい。最大値が負でも空部分列の 0 は候補に含めない。

#### 実装・検証

- [実装](../../segment-tree/segment-tree-max-of-interval.hpp)
- [検証: yuki-2281.test.cpp](../../verify/verify-yuki/yuki-2281.test.cpp)
- [検証: yuki-2333.test.cpp](../../verify/verify-yuki/yuki-2333.test.cpp)
