## 整数平方根

`isqrt(long long n)` は `floor(sqrt(n))`、n <= 0 では 0 を返す。浮動小数点の平方根を初期値として整数で補正する。

補正判定で `(x+1)*(x+1)` を long long で計算するため、型の最大値付近では積がオーバーフローする。全 64 bit 範囲に無条件で使える実装ではない。

#### 実装・検証

- [実装](../../math/isqrt.hpp)
- [検証: enumerate-convex.test.cpp](../../verify/verify-unit-test/enumerate-convex.test.cpp)
- [検証: math.test.cpp](../../verify/verify-unit-test/math.test.cpp)
