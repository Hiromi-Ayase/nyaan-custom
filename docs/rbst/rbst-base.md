## 乱択平衡二分木の基底

`RBSTBase<Node>` は部分木サイズを用いて乱択 merge を行う。Node は `l,r,cnt,key` を持ち、派生クラスが `push(node)` と `update(node)` を実装する。

`split(root,k)` は先頭 k 要素と残り、`merge(l,r)` は順に連結。`insert(root,k,...)`, `erase(root,k)`, `build(values)`, `size(root)` を提供する。根はポインタで管理し、split/merge は破壊的。

操作は期待 $O(\log n)$、構築は $O(n)$。空列の build は実装上利用できないので null root で表す。削除した要素以外の節点は自動で解放しない。

#### 実装・検証

- [実装](../../rbst/rbst-base.hpp)
- [Verify: reversible.cpp](../../tests/unit/rbst/reversible.cpp)
