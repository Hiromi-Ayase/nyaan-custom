## 多倍長整数での中国剰余定理

`garner_bigint(r,m)` / `crt_bigint(r,m)` は `(解, 法の積)` を bigint の組で返す。入力長は同じ、各 m は 2 以上 2×10^9 以下で互いに素、剰余は `[0,m[i])` に正規化して使う。

実装コメントは法 1 も許すが、下位逆元計算が法 1 に対応しないため、法 1 の制約は先に除く。非互いに素の場合の矛盾検出 API はない。空入力は `(0,1)`。

3000 件以下では素朴な $O(n^2)$ の混合基数計算、それより多い場合は多倍長積の分割統治を用いる。

#### 実装・検証

- [実装](../../math/bigint-garner.hpp)
- [検証: garner-bigint.test.cpp](../../verify/verify-unit-test/garner-bigint.test.cpp)
