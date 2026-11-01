## 線分の交差・距離

`Segment(a,b)` は Line を継承した線分。`is_intersect_sp(s,p)` は点が線分上か、`is_intersect_ss(s,t)` は端点接触を含む交差を判定する。

`distance_sp(s,p)` は点との距離、`distance_ss(s,t)` は二線分の距離。射影で長さの二乗を割るため、零長線分は別途処理する。

すべて $O(1)$。浮動小数点の EPS による判定を使用する。

#### 実装・検証

- [実装](../../geometry/segment.hpp)
- [Verify: lines-and-circles.cpp](../../tests/unit/geometry/lines-and-circles.cpp)
