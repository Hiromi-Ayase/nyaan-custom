## 平面幾何の基本型

`Real = long double`、`Point = PointBase<Real>`、`EPS = 1e-10` を定義する。Point は x/y、ベクトル加減算、スカラー倍、`rotate(rad)`、`dot/cross/abs/norm/arg` を持つ。norm は長さの二乗。

`equals/sign` は EPS を使うが、Point の `==` と辞書順比較は座標の厳密比較。`ccw(a,b,c)` は反時計回り +1、時計回り -1、一直線で c が a の後方なら +2、b の先なら -2、線分上なら 0。

演算は定数時間。零長ベクトルや誤差の尺度に注意する。整数幾何版も `Point` を定義するので同時に include しない。

#### 実装・検証

- [実装](../../geometry/geometry-base.hpp)
- [検証: aoj-cgl-1-c.test.cpp](../../verify/verify-aoj-cgl/aoj-cgl-1-c.test.cpp)
- [検証: geometry.test.cpp](../../verify/verify-unit-test/geometry.test.cpp)
