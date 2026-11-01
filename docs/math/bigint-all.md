## 多倍長整数・有理数の一括 include

bigint、BigRational、Rational、および有理数版の二項係数・形式的冪級数をまとめて読み込む。

例えば `FormalPowerSeries_rational<BigRational>` と `Binomial_rational<BigRational>` を使えば固定幅整数の上限を超える係数を扱える。演算コストは係数の分子・分母の桁数に依存する。

#### 実装・検証

- [実装](../../math/bigint-all.hpp)
- [Verify: big-rational.cpp](../../tests/unit/math/big-rational.cpp)
