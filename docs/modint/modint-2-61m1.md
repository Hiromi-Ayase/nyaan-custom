## 法 2^61−1 の modint

`modint_2_61m1` は Mersenne 素数 2^61−1 を法とする四則演算・比較・累乗を提供する。`get()` で値を取得し、`raw(x)` は正規化せず作るため `0 <= x < mod` が必要。

`inverse()` は非零値に限る。乗算は 128 bit の積を 61 bit で折り返す。内部 `modulo` もこの積の値域向けで、任意の 128 bit 整数の剰余計算ではない。

加減乗算は定数時間、非負指数の累乗は対数時間。

#### 実装・検証

- [実装](../../modint/modint-2-61m1.hpp)
- [検証: modint-2-61m1.test.cpp](../../verify/verify-unit-test/modint-2-61m1.test.cpp)
