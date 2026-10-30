## 有理数による組合せ計算

`Binomial_rational<R=Rational>` は `fac/finv/inv/C/P/H/multinomial` を有理数型 R で計算する。C は二項係数、P は順列、H は重複組合せ。operator() でも C・多項係数を呼べる。

階乗は必要に応じて拡張する。コンストラクタの整数引数は予約サイズとしては使われない。`inv(0)` は便宜上 1 を返すので数学的な逆元とは解釈しない。

固定幅の Rational は階乗・中間積ですぐにオーバーフローする。大きな n は BigRational を使用する。時間は拡張回数と有理数演算の桁数に依存する。

#### 実装・検証

- [実装](../../math/rational-binomial.hpp)
- [検証: bigrational.test.cpp](../../verify/verify-unit-test/bigrational.test.cpp)
- [検証: rational-number.test.cpp](../../verify/verify-unit-test/rational-number.test.cpp)
