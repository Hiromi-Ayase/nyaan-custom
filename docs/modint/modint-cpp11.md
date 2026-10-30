## 998244353 の C++11 用 modint

`MontgomeryModInt998244353` は法 998244353 固定の Montgomery modint。四則演算・比較・入出力・`get/get_mod`・非負指数の `pow` を提供する。

`inverse()` は Fermat の小定理による累乗なので零には使えない。メンバ a は内部表現であり、値の取得には get を使う。演算は定数時間、累乗・逆元は指数のビット数に比例する。

#### 実装・検証

- [実装](../../modint/modint-cpp11.hpp)
