## $\mathrm{floor}(a^{\frac{1}{k}})$

#### 概要

整数$a$の$k$乗根(切り捨て)を求めるライブラリ。

$a,k$の値によって`powl`関数が上下両方に誤差を発生しうることに注意して実装する。

#### 使い方

- `kth_root_integral(a, k)`　:　$a$の$k$乗根を求める。

#### 実装・検証

- [実装](../../math/kth-root-integral.hpp)
- [検証: yosupo-kth-root-integral.test.cpp](../../verify/verify-yosupo-math/yosupo-kth-root-integral.test.cpp)
