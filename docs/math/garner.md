## 整数型の中国剰余定理

`garner(rem,mod)` は `x ≡ rem[i] (mod mod[i])` の同時解を `(非負の解, 法の最小公倍数)` として返す。不整合なら `(0,0)`、空入力なら `(0,1)`。

`0 <= rem[i] < mod[i]`、`mod[i] >= 1` が必要。法は互いに素でなくてもよい。返り値は unsigned long long で、中間積・合成後の法もその範囲に収める。

各制約を拡張 Euclid 型の処理で併合する。`gcd_inv` はその内部用の符号なし逆元計算。

#### 実装・検証

- [実装](../../math/garner.hpp)
- [Verify: elementary.cpp](../../tests/unit/math/elementary.cpp)
