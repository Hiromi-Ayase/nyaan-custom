## 集合冪級数の指数関数

`exp_of_set_power_series<mint,MAX=21>(n,g)` は部分集合畳み込みを積とする集合冪級数の `exp(g)` を返す。`0 <= n <= MAX`、空集合の係数 `g[0]==0` が必要。

`g` は長さ `2^n` に resize される。結果の空集合係数は 1。最大要素による分割で、各集合の分割に対する積の総和を計算する。

Subset Convolution を用い、時間 $O(n^2 2^n)$、内部のランク付き表に $O(MAX\,2^n)$ の領域を使用する。

#### 実装・検証

- [実装](../../set-function/exp-of-set-power-series.hpp)
- [検証: yosupo-exp-of-set-power-series.test.cpp](../../verify/verify-yosupo-graph/yosupo-exp-of-set-power-series.test.cpp)
