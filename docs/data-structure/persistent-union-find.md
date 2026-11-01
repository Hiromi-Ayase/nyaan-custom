## 完全永続 Union Find

`PersistentUnionFind(n)` は永続配列に親とサイズを保存する。

`find(i,r)`, `size(i,r)`, `same(i,j,r)` で根 `r` の版を参照し、`unite(i,j,r)` で併合する。成功時は現在の根が新しい版に変わり、`get_root()` で取得できる。引数 `r` の省略時は現在の根を使う。

`unite` がすでに同じ成分を受け取った場合は `false` を返し、現在の根を指定版へ切り替えない。`root` は static なので、複数インスタンス間で共有される点にも注意する。

経路圧縮せずサイズ併合する。永続配列のアクセス込みで各操作は $O(\log^2 n)$、成功した更新の追加領域は $O(\log n)$（固定分岐数）。

#### 実装・検証

- [実装](../../data-structure/persistent-union-find.hpp)
- [Verify: persistent.cpp](../../tests/unit/data-structure/persistent.cpp)
