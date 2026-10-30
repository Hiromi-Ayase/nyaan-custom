## 連続区間を併合する Union Find

`RangeUnionFind(n)` に対し、`range_unite(l,r)` は半開区間 `[l,r)` の全要素を同じ成分にする。範囲外の端点は `[0,n]` に切り詰める。

`find`, `same`, `size` と根の `left`, `right`（成分の半開区間）を参照できる。`unite(x,y)` も公開されるが、成分が常に連続区間になるよう隣接成分だけを併合する。離れた成分を直接併合すると `range_unite` の前提が壊れる。

成功する併合は全体で高々 `n-1` 回。$Q$ 回の区間併合は合計 $O((n+Q)\alpha(n))$、領域は $O(n)$。

#### 実装・検証

- [実装](../../data-structure/range-union-find.hpp)
- [検証: yuki-1170.test.cpp](../../verify/verify-yuki/yuki-1170.test.cpp)
