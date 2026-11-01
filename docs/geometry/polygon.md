## 多角形・凸包

`Polygon` は Point の配列。`area(p)` は符号付き面積で、反時計回りが正。`contains_polygon(p,x)` は外 0・境界 1・内 2 を返す。

`convex_hull<boundary=false>(points)` は重複を除いた凸包を反時計回りで返す。`boundary=true` は辺上の点も残すが、全点が共線の場合の重複に注意する。

`contains_convex(p,x)` は反時計回りの凸多角形を二分探索し、同じ 0/1/2 を返す。少なくとも三頂点の非退化な凸包が必要。`convex_polygon_diameter(p)` は最遠点対の頂点番号を返し、非空の凸多角形を前提とする。

面積・一般の内外判定・直径は $O(n)$、凸包構築 $O(n\log n)$、凸包の内外判定 $O(\log n)$。

#### 実装・検証

- [実装](../../geometry/polygon.hpp)
- [Verify: polygons.cpp](../../tests/unit/geometry/polygons.cpp)
