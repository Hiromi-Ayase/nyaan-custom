## 円の位置関係と交点

`Circle(center,radius)` は中心と半径を保持する。`intersect(c1,c2)` は位置関係を整数で返す。

| 値 | 関係 |
| --- | --- |
| 0 | 一方が他方の内部にあり接しない |
| 1 | 内接 |
| 2 | 二点で交わる |
| 3 | 外接 |
| 4 | 外側で離れている |

`crosspoint(c1,c2)` は二つの交点を返す。接するときは同じ点が二つ。正の半径・異なる中心で、交点があることを先に保証する。同一円は有限個の交点という API の対象外。時間 $O(1)$。

#### 実装・検証

- [実装](../../geometry/circle.hpp)
- [Verify: lines-and-circles.cpp](../../tests/unit/geometry/lines-and-circles.cpp)
