## Stern–Brocot 木

`SternBrocotTreeNode<Int>(x,y)` は正の有理数 x/y を既約化して保持する。既定値は 1/1。`get()` は分子分母、`lower_bound/upper_bound()` は両側の隣接分数。

`go_left/right(d)` は同方向に d 回、`go_parent(d)` は親方向へ移動する。親へ十分進めなければ false（移動済み状態は戻らない）。`depth()` と static の `lca(a,b)` も提供する。

`seq` は右を正・左を負にした連長圧縮経路。ただし seq を直接受けるコンストラクタは負の値を go_left にそのまま渡す不整合があるため、分数または移動 API から構築する。計算量は圧縮経路長に依存する。

#### 実装・検証

- [実装](../../math/stern-brocot-tree.hpp)
- [検証: yosupo-stern-brocot-tree-2.test.cpp](../../verify/verify-yosupo-math/yosupo-stern-brocot-tree-2.test.cpp)
- [検証: yosupo-stern-brocot-tree.test.cpp](../../verify/verify-yosupo-math/yosupo-stern-brocot-tree.test.cpp)
