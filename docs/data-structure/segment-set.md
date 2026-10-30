## 互いに重ならない区間の集合

`SegmentSet<T>` は半開区間の和集合を map で保持する。`insert(l,r)` は重なる・接する区間を結合し、`erase(l,r)` は必要なら区間を分割して削除する。`l < r` を満たす区間を渡す。

`find(x)` は `x` を含む区間、`lower_bound(x)` は `x` を含むか、その右にある最初の区間の iterator。該当なしは `end()`。`next(x)` は集合中の `x` 以上の最小値で、なければ `numeric_limits<T>::max()`。`size()` は点数ではなく区間数。

区間数を $s$、変更される区間数を $k$ とすると、検索は $O(\log s)$、更新は $O(\log s+k)$。

#### 実装・検証

- [実装](../../data-structure/segment-set.hpp)
- [検証: segment-set.test.cpp](../../verify/verify-unit-test/segment-set.test.cpp)
