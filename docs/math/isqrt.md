## 整数平方根

`isqrt(long long n)` は `floor(sqrt(n))`、n <= 0 では 0 を返す。浮動小数点の平方根を初期値として整数で補正する。

補正判定の積は128 bit整数で計算するため、`long long` の最大値付近でもオーバーフローせずに判定する。

#### 実装・検証

- [実装](../../math/isqrt.hpp)
- [Verify: integer-roots.cpp](../../tests/unit/math/integer-roots.cpp)
