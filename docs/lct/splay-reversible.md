## 反転可能 Splay Tree

`ReversibleSplayTree<T,f,ts>` は Splay Tree 基底と反転対応の集約を組み合わせる。`build(v)` の返す根に対し、半開区間の `fold/reverse` と列の `insert/erase/split/merge` を行う。

`f` の単位元は `T()`、`ts` は反転時の集約変換。和など可換な演算では恒等変換でよい。非可換な演算は逆順の情報も保持する。

操作は破壊的で、参照引数の根を更新する。独立した列へのコピーでは節点を共有しないよう管理する。単発の最悪時間は $O(n)$。

#### 実装・検証

- [実装](../../lct/splay-reversible.hpp)
- [検証: yosupo-dynamic-tree-vertex-set-path-composite.test.cpp](../../verify/verify-yosupo-ds/yosupo-dynamic-tree-vertex-set-path-composite.test.cpp)
- [検証: yosupo-range-reverse-range-sum.test.cpp](../../verify/verify-yosupo-ds/yosupo-range-reverse-range-sum.test.cpp)
