## 一次式の積を分母とする部分分数分解

`PartialFractionDecomposition(f,b)` は $f(x)/\prod_i(x-b_i)$ を $\sum_i a_i/(x-b_i)$ と分解し、`b` と同じ順で `a` を返す。`b_i` は係数体上で相異なり、`f.size() <= b.size()` とする。

重根を扱う版は `PartialFractionDecomposition(numer, denom)` で、`denom` は `(m,d)` の配列。この版の因子は **$(x+m)^d$**。返り値 `(m, coefficients)` の `coefficients[j]` は $1/(x+m)^{j+1}$ の係数になる。異なる組の `m` は相異なり、各 `d` は正とする。出力順は次数でソートされた分母の順で、入力順とは限らない。

重根版は分子を分母全体で剰余にしてから処理するため、分子の次数が高い場合の多項式部分は返さない。全体を表すには多項式除算で得た商を別に保持する。

積の木と剰余・Taylor shift を利用する。分母の総次数を $N$ として、高速 FPS 演算では時間 $O(N\log^2 N)$、領域 $O(N\log N)$。係数の差と必要な階乗が可逆であることが必要。

#### 実装・検証

- [実装](../../fps/partial-fraction-decomposition.hpp)
- [検証: partial-fraction-decomposition.test.cpp](../../verify/verify-unit-test/partial-fraction-decomposition.test.cpp)
- [検証: yuki-1510.test.cpp](../../verify/verify-yuki/yuki-1510.test.cpp)
