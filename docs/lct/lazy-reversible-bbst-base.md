## 遅延・反転対応平衡木の基底

`LazyReversibleBBST<Tree,Node,T,E,f,g,h,ts>` は半開区間の `fold`, `reverse`, `apply` を提供する。

`f` は結合、`ts` は反転、`g` は一点値と区間集約の両方に適用できる作用。`h(old,new)` はその順の合成。`T()` と `E()` を単位元とし、作用と反転の整合性も必要。

`apply` は空区間の null 節点を処理しないため、必ず `l < r` とする。root は操作で変更される。計算量は基礎の木の split/merge に従う。

#### 実装・検証

- [実装](../../lct/lazy-reversible-bbst-base.hpp)
- [Verify: splay-sequences.cpp](../../tests/unit/lct/splay-sequences.cpp)
