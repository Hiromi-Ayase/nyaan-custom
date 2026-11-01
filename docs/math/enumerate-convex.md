## 判定関数から下側凸包を列挙

`enumerate_convex(xl,yl,xr,inside,candicate)` は整数格子上の下側凸包を `(xl,yl)` から x の昇順に列挙する。始点は内部かつその直下は外部であることが必要。

`inside(x,y)` は領域内判定。`candicate(x,y,c,d)` は外部点から方向 `(c,d)` に進んで内部へ入れる整数 s が存在すれば、その一つを返す。存在しなければ -1 などを返す。

一般の点集合を渡す凸包 API ではなく、凸性と探索方向に整合する領域・候補関数が必要。時間は出力頂点数、方向探索、二分探索、コールバックのコストに依存する。

#### 実装・検証

- [実装](../../math/enumerate-convex.hpp)
- [Verify: stern-brocot.cpp](../../tests/unit/math/stern-brocot.cpp)
