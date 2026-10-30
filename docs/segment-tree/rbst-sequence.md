## RBST による可変長列

`Sequence<T,E,f,g,h,ti,ei>` は挿入・削除で添字が移動する列。空、`(n)`、`(vector<T>)` から構築する。演算の条件は RBST 遅延 Segment Tree と同じ。

- `insert(i,x)`, `push_back(x)`: 位置 `i` の直前・末尾への挿入。
- `erase(i)`, `erase(l,r)`, `pop_back()`: 一点・半開区間・末尾の削除。
- `append(other)`: 列を末尾へ連結し、`other` を空にする。配列の追加も可能。
- 継承した `set_val`, `get_val`, `apply`, `fold`, `size` を使える。添字は常に `[0,size())` に収める。
- `get_vector()`: 現在の列を配列として取得する。

一点操作・区間集約・作用は期待 $O(\log n)$。区間削除は削除要素数 $k$ に対し期待 $O(k+\log n)$、配列変換は $O(n)$。コピーは節点を共有するので独立した列として更新しない。空列の削除や自身の `append` は行わない。

#### 実装・検証

- [実装](../../segment-tree/rbst-sequence.hpp)
- [検証: rbst-sequence.test.cpp](../../verify/verify-unit-test/rbst-sequence.test.cpp)
