## 固定法の modint

`ModInt<mod>` は加減乗除、比較、符号反転、`pow(n)`、`inverse()`、入出力を提供する。`get()` は `[0,mod)` の値、`get_mod()` は法。

正の固定法を用い、加減算で `int` がオーバーフローしないよう通常は mod < 2^30 とする。逆元は拡張 Euclid によるため、素数法でなくてもよいが被除数と法が互いに素である必要がある。失敗検出は行わない。

累乗は非負指数。加減乗算 $O(1)$、累乗・逆元は対数時間。

#### 実装・検証

- [実装](../../modint/modint.hpp)
- [検証: modint.test.cpp](../../verify/verify-unit-test/modint.test.cpp)
- [検証: yosupo-convolution-ntt-normalmodint.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-ntt-normalmodint.test.cpp)
