## 0-1ナップサック問題

### 概要

> 0-1ナップサック問題
>
> 品物が$N$個(品物$0$から品物$N-1$)あり、品物$i$は価値$v_i$重さ$w_i$である。重さの総和が$W$以下となるようにいくつかの品物を選んだとき、選んだ品物の価値の総和の最大値$V_{\max}$を求めよ。

### 使い方

- `knapsack01(v,w,W)`: 数列$v=\{v_i\}$,$w=\{w_i\}$と値$W$を与えると、0-1ナップサック問題を解いて解$V_{\max}$を返す。計算量$\mathrm{O}(\min \lbrace N W , N \sum v_i , N 2^{\frac{N}{2}} \rbrace )$

#### 実装・検証

- [実装](../../dp/knapsack01.hpp)
- [検証: aoj-dpl-1-b.test.cpp](../../verify/verify-aoj-dpl/aoj-dpl-1-b.test.cpp)
- [検証: aoj-dpl-1-f.test.cpp](../../verify/verify-aoj-dpl/aoj-dpl-1-f.test.cpp)
- [検証: aoj-dpl-1-h.test.cpp](../../verify/verify-aoj-dpl/aoj-dpl-1-h.test.cpp)
