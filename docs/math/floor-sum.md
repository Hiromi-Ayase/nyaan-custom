## 床関数の総和

`sum_of_floor(n,m,a,b)` は `Σ_{i=0}^{n-1} floor((a*i+b)/m)` を返す。`n,a,b >= 0`、`m > 0` を前提とする。

`mod_affine_range_counting(a,b,m,xr,yr)` は `0 <= x < xr` のうち `(a*x+b) mod m < yr` の個数。`0 <= yr <= m` とする。

Euclid 型の再帰により対数回の整数演算を行う。二乗項・中間積・最終結果が型 T に収まる必要がある。

#### 実装・検証

- [実装](../../math/floor-sum.hpp)
- [Verify: floor-and-quotient.cpp](../../tests/unit/math/floor-and-quotient.cpp)
