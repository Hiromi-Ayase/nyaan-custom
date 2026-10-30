## 有理数係数の形式的冪級数

`FormalPowerSeries_rational<R=Rational>` は定数項から並べた vector<R> を継承する。多項式の加減乗除・剰余、係数反転 `rev`、先頭項 `pre`、係数積 `dot`、シフト、微積分、評価を提供する。

`inv(deg)` は定数項非零、`log(deg)` は定数項 1、`exp(deg)` は定数項 0、`pow(k,deg)` は非負整数 k が前提。`/` は多項式除算で、冪級数の除算は inv を掛ける。

乗算は素朴法 $O(nm)$ 回の有理数演算。空同士の乗算や零多項式による除算は避ける。係数の分子・分母の増大に注意し、必要なら BigRational を使う。

#### 実装・検証

- [実装](../../math/rational-fps.hpp)
- [検証: bigrational.test.cpp](../../verify/verify-unit-test/bigrational.test.cpp)
- [検証: rational-number.test.cpp](../../verify/verify-unit-test/rational-number.test.cpp)
