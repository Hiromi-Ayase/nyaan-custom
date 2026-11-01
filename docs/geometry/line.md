## 直線・射影・凸多角形の切断

`Line(a,b)` または `Line(A,B,C)`（`A*x+B*y=C`）で直線を作る。二点は異なること、係数は A/B の少なくとも一方が非零であることが必要。

`is_parallel/is_orthogonal` は平行・直交、`is_intersect_ll` は交差判定、`cross_point_ll` は交点。同一直線なら後者は一方の端点を返す。平行で異なる直線には交点取得を呼ばない。

`projection(line,p)` は垂足。`convex_polygon_cut(poly,line)` は直線 a→b の左側を残す。基本操作 $O(1)$、切断は頂点数に比例する。

#### 実装・検証

- [実装](../../geometry/line.hpp)
- [Verify: lines-and-circles.cpp](../../tests/unit/geometry/lines-and-circles.cpp)
- [Verify: polygons.cpp](../../tests/unit/geometry/polygons.cpp)
