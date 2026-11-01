## 遅延・反転対応 Splay Tree

`LazyReversibleSplayTree<T,E,f,g,h,ts>` は反転可能 Splay Tree に遅延作用を加えたもの。`fold`, `reverse`, `apply` は半開区間で、`apply` には非空区間を渡す。

`T()` は集約の単位元、`E()` は作用の単位元。`g(T,E)` は一点と集約の両方に正しく作用させ、`h(old,new)` は古い作用の後に新しい作用を行う。`ts` は反転後の集約を返す。

根は build/split/merge で取得・更新する。Node の lazy を直接書き換えず公開操作を使う。計算量は Splay Tree 基底に従い、単発の最悪時間は $O(n)$。

#### 実装・検証

- [実装](../../lct/splay-lazy-reversible.hpp)
- [Verify: splay-sequences.cpp](../../tests/unit/lct/splay-sequences.cpp)
