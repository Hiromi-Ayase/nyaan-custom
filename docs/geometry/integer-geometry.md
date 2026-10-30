## 整数平面幾何

座標型を `__int128_t` とする Point、内積 `dot`、外積 `cross`、向き判定 `ccw` を提供する。ccw は反時計回り 1、共線 0、時計回り -1。

`ArgumentSort(points)` は偏角順に破壊的ソートする。`LowerHull/UpperHull` は x 座標順の点列から下側・上側の凸包を作る。`ConvexHull` は自分で辞書順ソート・重複除去し、辺上の中間点を除く凸包を返す。

積も 128 bit に収まること。入出力演算は long long に制限される。凸包構築は $O(n\log n)$、ソート済み片側凸包は $O(n)$。浮動小数点版の Point と併用しない。

#### 実装・検証

- [実装](../../geometry/integer-geometry.hpp)
- [検証: yosupo-argument-sort.test.cpp](../../verify/verify-yosupo-other/yosupo-argument-sort.test.cpp)
- [検証: yosupo-static-convex-hull-2.test.cpp](../../verify/verify-yosupo-other/yosupo-static-convex-hull-2.test.cpp)
