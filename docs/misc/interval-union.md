## 半開区間の和集合

`interval_union(v)` は `(l,r)` の半開区間列をソートし、重なる区間・端点で接する区間をまとめて返す。入力は変更しない。

各区間は `l <= r` とする。空区間は自動では除去されないため、不要なら入力前に取り除く。時間 $O(n\log n)$、領域 $O(n)$。

#### 実装・検証

- [実装](../../misc/interval-union.hpp)
- [Verify: basic-utilities.cpp](../../tests/unit/misc/basic-utilities.cpp)
