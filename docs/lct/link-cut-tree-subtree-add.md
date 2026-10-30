## 部分木加算・部分木和 Link/Cut Tree

`LinkCutTreeSubtreeQuery<T,add,sub,mul>` は `Node(value)` のポインタで動的な森を管理する。`add/sub` は加減算、`mul(value,count)` は整数倍、`T()` は零。内部で通常の `operator-` も使う。

`link(u,v)`, `cut(u,v)`、`evert(root)`、`set_key/get_key` を提供する。`subtree_add(v,x)` は現在の根に対する部分木へ加算し、`subtree_sum(v)` はその和。

根を指定した問い合わせでは直前に evert する。link は異なる木、cut は既存の辺のみ。基本操作は償却 $O(\log n)$。非加算版と同名のクラスを定義するため同時に include しない。

#### 実装・検証

- [実装](../../lct/link-cut-tree-subtree-add.hpp)
- [検証: yosupo-dynamic-tree-subtree-add-subtree-sum.test.cpp](../../verify/verify-yosupo-ds/yosupo-dynamic-tree-subtree-add-subtree-sum.test.cpp)
- [検証: yosupo-dynamic-tree-vertex-add-subtree-sum-2.test.cpp](../../verify/verify-yosupo-ds/yosupo-dynamic-tree-vertex-add-subtree-sum-2.test.cpp)
