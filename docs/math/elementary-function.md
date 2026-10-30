## 基本整数関数

`EulersTotientFunction(N)` は `[0,N]` の φ 表、`phi(n)` は一点の φ。`Divisor(N)` は正の約数を返すが、昇順ではない。`PrimeFactors(N)` は試し割りによる `(素数,指数)`、素数列を渡す版では必要な素数を十分に用意する。

`modpow(a,n,mod)` は非負指数・正の 2^31 未満の法向け。`isPrimitiveRoot/PrimitiveRoot` は素数法を前提とする。`extgcd(a,b)` は Bezout 係数を返し、負入力では GCD の符号に注意する。

`SqrtInt(n)` は完全平方なら平方根、そうでなければ -1。`isDigit(n,zero=1)` は十進桁数。試し割り・約数列挙は $O(\sqrt n)$、累乗・拡張 Euclid は対数時間。境界の二乗オーバーフローを避ける。

#### 実装・検証

- [実装](../../math/elementary-function.hpp)
- [検証: aoj-ntl-1-a.test.cpp](../../verify/verify-aoj-ntl/aoj-ntl-1-a.test.cpp)
- [検証: aoj-ntl-1-b.test.cpp](../../verify/verify-aoj-ntl/aoj-ntl-1-b.test.cpp)
- [検証: aoj-ntl-1-c.test.cpp](../../verify/verify-aoj-ntl/aoj-ntl-1-c.test.cpp)
