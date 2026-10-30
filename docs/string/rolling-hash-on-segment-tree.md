## 一点更新できる Rolling Hash

`RollingHashonSegmentTree<Str>(s)` は列のハッシュと長さを Segment Tree で管理する。

`update(i,value)` で一要素を変更し、`same(l1,r1,l2,r2)` で二つの半開区間の一致を判定する。長さが異なれば偽。元の列を参照せず、ハッシュとして保持する。

構築・領域 $O(n)$、更新・比較 $O(\log n)$。基数を乱数で選ぶハッシュなので、真でも衝突の可能性がある。厳密な一致証明として扱わない。

#### 実装・検証

- [実装](../../string/rolling-hash-on-segment-tree.hpp)
- [関連検証（間接使用）: parallel-union-find.test.cpp](../../verify/verify-unit-test/parallel-union-find.test.cpp)
- [関連検証（間接使用）: yosupo-range-parallel-unionfind.test.cpp](../../verify/verify-yosupo-ds/yosupo-range-parallel-unionfind.test.cpp)
