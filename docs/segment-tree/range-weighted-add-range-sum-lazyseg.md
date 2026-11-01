## 重み付き区間加算・区間和

各要素 `(value, weight)` に対し、更新量 `x` を `value += x * weight` として反映する。重みは初期値として与える。

`Range_Weighted_Add_Range_Sum_SegTree<T,E>(v)` の `T` は `.first` に値、`.second` に重みを持つ型（例えば `pair<long long,long long>`）、`E` は加算量・返却値の型。

- `update(l,r,x)` / `query(l,r)`: 半開区間 `[l,r)` の更新・値の総和。
- `update(i,x)` / `query(i)`: 一点の更新・取得。
- `set_val(i,x)`: 一点の値と重みを置き換える。ただし祖先の重み和は再計算しないため、重みは元と同じにする。

範囲操作には非空区間を渡す。構築は $O(n)$、各操作は $O(\log n)$、領域は $O(n)$。

#### 実装・検証

- [実装](../../segment-tree/range-weighted-add-range-sum-lazyseg.hpp)
- [Verify: utilities.cpp](../../tests/unit/segment-tree/utilities.cpp)
