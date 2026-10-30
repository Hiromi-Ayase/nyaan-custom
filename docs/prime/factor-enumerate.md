## 最小素因数の列挙

`factor_enumerate(N)` は `[0,N]` の最小素因数表を返す。素数 `p` は `table[p]==p`、0 と 1 は 0。

`n >= 2` なら `table[n]` で割り続けて素因数分解できる。`N` は非負とし、内部の `int` の積がオーバーフローしない範囲で使う。

線形篩により時間・領域 $O(N)$。

#### 実装・検証

- [実装](../../prime/factor-enumerate.hpp)
- [関連検証（間接使用）: factorize.test.cpp](../../verify/verify-unit-test/factorize.test.cpp)
- [関連検証（間接使用）: osak.test.cpp](../../verify/verify-unit-test/osak.test.cpp)
