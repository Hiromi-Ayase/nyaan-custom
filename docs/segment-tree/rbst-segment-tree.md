## RBST による動的 Segment Tree

乱択平衡二分木で疎なキーと値を管理する。非遅延版 `RBSTSegmentTree<I,T,f,ti>`、遅延版 `RBSTLazySegmentTree<I,T,E,f,g,h,ti,ei>`、キーを一括平行移動できる `RBSTShiftableLazySegmentTree` を提供する。

- 空のコンストラクタ、または `(values, keys={})` で構築する。キー指定時は狭義昇順、未指定時は `0,1,...`。
- `set_val(i,x)`, `get_val(i)`, `exist(i)`, `erase(i)`: 一点の操作。未登録の値は `ti()`。
- `apply_val(i,func)`: `func(T&)` で値を直接変更する。`*_fast` 版は既存キーへの更新を優先する。
- `fold(l,r)`, `fold_all()`: キーの半開区間・全体の積。遅延版では `apply(l,r,e)`, `apply_all(e)` も使える。
- `split_by_key(k)`: `< k` と `>= k` に分け、元を空にする。`ordered_merge(a,b)` は全キーが `a < b` のとき破壊的に結合する。
- `min_left`, `max_right` とその端点の包含を変えた版は、単位元で真となる単調な述語で境界を探す。見つからない場合の値を引数で指定する。
- `make_array()` はキー順の `(key,value)` 列。`clear()` は節点を解放する。

`f` は結合的、`g` は集約値にも適用可能な作用、`h(old,new)` は順に適用する合成。コピーは節点を共有するため、独立したコピーには `deepcopy()` を使う。通常操作は期待 $O(\log n)$、列への変換・解放は $O(n)$。

#### 実装・検証

- [実装](../../segment-tree/rbst-segment-tree.hpp)
- [検証: rbst-segment-tree.test.cpp](../../verify/verify-unit-test/rbst-segment-tree.test.cpp)
- [検証: yosupo-associative-array-rbstseg.test.cpp](../../verify/verify-yosupo-ds/yosupo-associative-array-rbstseg.test.cpp)
- [検証: yosupo-point-set-range-composite-rbstseg.test.cpp](../../verify/verify-yosupo-ds/yosupo-point-set-range-composite-rbstseg.test.cpp)
