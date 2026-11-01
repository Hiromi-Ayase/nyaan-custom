## 階乗・二項係数の対数

`FloatBinomial(MAX)` は `log(n!)` を long double で前計算する。

`logfac(n)`, `logfinv(n)`, `logC(n,k)`, `logP(n,k)` を定数時間で返す。C/P の不正な n,k は負の番兵 `LOGZERO=-1e10` で、厳密な負の無限大ではない。引数は前計算上限以下にする。

前処理・領域 $O(MAX)$。大きな組合せ数の比や確率を対数で扱う用途であり、整数値の厳密計算ではない。

#### 実装・検証

- [実装](../../math/float-binomial.hpp)
- [Verify: rational.cpp](../../tests/unit/math/rational.cpp)
