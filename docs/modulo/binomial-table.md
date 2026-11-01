## Pascal の三角形

`binomial_table<T>(n)` は二項係数 `C(i, j)` の表を返す。実装は余裕として `n+10` 行・列を確保し、`0 <= i,j < n+10` を持つ。`j > i` の値は `0`。

`C(0,0)=1` と Pascal の漸化式だけを使い、除算は不要。整数や任意の法の modint で使えるが、整数型では値のオーバーフローに注意する。`n` は非負。

時間・領域ともに $O((n+10)^2)$。大きい範囲を多数問い合わせる場合、素数の法なら階乗を使う `Binomial` も利用できる。

#### 実装・検証

- [実装](../../modulo/binomial-table.hpp)
- [Verify: binomial.cpp](../../tests/unit/modulo/binomial.cpp)
