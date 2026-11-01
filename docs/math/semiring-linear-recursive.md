## 半環上の線形漸化式

`LinearRecursive<rig>(C)` は `a[t] = C[0]*a[t-1] + ... + C[N-1]*a[t-N]` の第 k 項を求める。`kth_term(initial,k)` には N 個の初期値を渡す。

rig は半環の演算 `+/*`、`rig::id0()`、`rig::id1()` を提供する。係数と値の積が期待する順序で成り立つこと（通常は可換な半環）。N>0、k>=0 とする。`get_coeff(k)` は初期値の逆順に対応する係数列。

時間 $O(N^2\log k)$ 回の半環演算。減算・除算を使わない。

#### 実装・検証

- [実装](../../math/semiring-linear-recursive.hpp)
- [Verify: semiring.cpp](../../tests/unit/math/semiring.cpp)
