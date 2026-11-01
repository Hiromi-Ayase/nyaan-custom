## 区間加算・区間和 BIT

`RangeAddRangeSumBIT<T>(n)` は初期値 0 の列を二つの BIT で管理する。

`add(l,r,x)` は半開区間 `[l,r)` に `x` を加え、`sum(l,r)` は同じ半開区間の和を返す。添字は 0 始まり。`T` には加減算と整数倍が必要で、中間積も型に収まること。

構築・領域は $O(n)$、各操作は $O(\log n)$。内部の通常 BIT の閉区間 API とは端点規約が異なる。

#### 実装・検証

- [実装](../../data-structure/range-sum-range-add-bit.hpp)
- [Verify: fenwick.cpp](../../tests/unit/data-structure/fenwick.cpp)
