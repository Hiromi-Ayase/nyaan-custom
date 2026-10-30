## 多倍長有理数

`BigRational` は `RationalBase<bigint,bigint>` の別名。分子・分母と比較時の積を多倍長整数で計算する。

四則演算・比較・逆元などは RationalBase と同じ。分母は非零とする。`to_double(r)` は近似実数へ変換し、値域によっては丸めやオーバーフロー・アンダーフローが生じる。

計算量は分子分母の桁数、bigint の四則演算と GCD に依存する。

#### 実装・検証

- [実装](../../math/bigint-rational.hpp)
- [検証: aoj-2171-bigrational.test.cpp](../../verify/verify-aoj-other/aoj-2171-bigrational.test.cpp)
- [検証: bigrational.test.cpp](../../verify/verify-unit-test/bigrational.test.cpp)
