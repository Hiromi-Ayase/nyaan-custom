## ポテンシャル付き Union Find

`UnionFindWithPotential<T>(n)` は頂点の値の差を加法的に管理する。

`merge(x,y,p)` は **`P(x) = P(y) + p`** という制約を追加し、整合すれば `true`、既存制約に矛盾すれば `false`。`diff(x,y)` は `P(x)-P(y)` で、`same(x,y)` が真のときにだけ意味を持つ。

`root`, `size`, `potential(x)`（根からの差）も提供する。`T` は零・加減算・符号反転・等値比較に対応すること。各操作は償却 $O(\alpha(n))$、領域は $O(n)$。

#### 実装・検証

- [実装](../../data-structure/union-find-with-potential.hpp)
- [Verify: union-find-with-potential.cpp](../../tests/unit/data-structure/union-find-with-potential.cpp)
