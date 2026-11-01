## 遅延・反転対応 Treap

`LazyReversibleTreap<T,E,f,g,h,ts>` は暗黙添字の列。`build(v)` の返す根を保持し、`insert/erase`、`fold(root,l,r)`、`reverse(root,l,r)`、`apply(root,l,r,e)` を呼ぶ。区間は半開。

`f` は結合、`g` は値と集約への作用、`h(old,new)` は作用合成、`ts` は反転後の集約への変換。`T()` と `E()` がそれぞれ単位元であること。

空列の build と空区間の apply は未対応。削除された節点もこの実装では解放しない。構築 $O(n)$、操作は期待 $O(\log n)$、節点数に比例する領域を使用する。

#### 実装・検証

- [実装](../../rbst/treap.hpp)
- [Verify: reversible.cpp](../../tests/unit/rbst/reversible.cpp)
