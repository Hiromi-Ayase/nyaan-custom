## パス作用付き Link/Cut Tree

`LazyLinkCutTree<T,E,f,g,h,ts>` は動的な森のパス集約・作用を扱う。節点を `my_new(value)` で作り、継承した `link`, `cut`, `evert`, `query` を使用する。

`apply(u,v,e)` は両端を含む u-v パスへ作用、`set_key/get_key` は一点値の操作。`T` に区間長などを含め、`g` が一点と集約を同じ形で更新できるようにする。`h(old,new)` は順に作用する合成、`ts` は逆向きの集約変換。

link は異なる木、cut は実在する辺、パス操作は同じ木の頂点で行う。根は evert や操作により変わる。基本操作は償却 $O(\log n)$。

#### 実装・検証

- [実装](../../lct/link-cut-tree-lazy.hpp)
- [Verify: paths.cpp](../../tests/unit/lct/paths.cpp)
