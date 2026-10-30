## 要素列挙付き Union Find

`UnionFindEnumerate(n)` は通常の `find`, `unite`, `same`, `size` に、`enumerate(i)`（`i` と同じ成分の全頂点）を加えたもの。

`unite(x,y,f)` は成功時に `f(新しい根, 吸収される根)` を呼ぶ。呼び出し時は親・サイズの更新後だが列挙用の循環リストを連結する前なので、吸収側の元の要素を列挙できる。

併合・検索は償却 $O(\alpha(n))$、列挙は成分サイズに比例し、領域は $O(n)$。列挙順は頂点番号順とは限らない。

#### 実装・検証

- [実装](../../data-structure/union-find-enumerate.hpp)
- [関連検証（間接使用）: parallel-union-find.test.cpp](../../verify/verify-unit-test/parallel-union-find.test.cpp)
- [関連検証（間接使用）: yosupo-range-parallel-unionfind.test.cpp](../../verify/verify-yosupo-ds/yosupo-range-parallel-unionfind.test.cpp)
