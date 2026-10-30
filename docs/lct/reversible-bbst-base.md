## 反転可能な平衡二分木の基底

`ReversibleBBST<Tree,Node,T,f,ts>` は split/merge を持つ木に区間集約と反転を追加する。

`fold(root,l,r)` は半開区間の積、`reverse(root,l,r)` は反転。`f` は結合的で単位元は `T()`。`ts` は列順を反転した集約を返し、`ts(f(a,b)) == f(ts(b),ts(a))` を満たすよう設計する。

操作後は参照引数 root が更新される。時間は基礎となる木の split/merge に従う。通常は `ReversibleSplayTree` から利用する。

#### 実装・検証

- [実装](../../lct/reversible-bbst-base.hpp)
- [関連検証（間接使用）: yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp](../../verify/verify-yosupo-ds/yosupo-dynamic-tree-vertex-add-subtree-sum.test.cpp)
- [関連検証（間接使用）: yosupo-dynamic-tree-vertex-set-path-composite.test.cpp](../../verify/verify-yosupo-ds/yosupo-dynamic-tree-vertex-set-path-composite.test.cpp)
- [関連検証（間接使用）: yosupo-offline-dynamic-connectivity.test.cpp](../../verify/verify-yosupo-ds/yosupo-offline-dynamic-connectivity.test.cpp)
