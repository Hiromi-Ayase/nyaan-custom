## 部分木集約付き Link/Cut Tree

`LinkCutTreeSubtreeQuery<T,f,finv>` は仮想辺側の寄与も保持する Link/Cut Tree。`f` は可換な群の結合、`finv(a,b)` は b の寄与を a から取り除く演算、`T()` は単位元。

`subtree(v)` は現在の根に対する v 以下の集約。根を指定する場合は先に `evert(root)` を呼ぶ。`set_key` と通常の link/cut 操作も使える。

辺操作は森を維持し、パス上の値だけを集約する通常版とは sum の意味が異なる。各基本操作は償却 $O(\log n)$。加算対応の別実装とクラス名が衝突する。

#### 実装・検証

- [実装](../../lct/link-cut-tree-subtree.hpp)
- [Verify: subtree.cpp](../../tests/unit/lct/subtree.cpp)
