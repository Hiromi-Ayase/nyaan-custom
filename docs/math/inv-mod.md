## 整数の逆元

`inv_mod(a,m)` は m を法とする a の非負逆元を返す。`m==1` は 0。通常は `m > 1`、`gcd(a,m)==1` とする。

逆元がない場合は失敗値を返さず、0 除算に至る。負の a の補正は一度だけなので、`a < -m` は先に非負剰余へ正規化する。内部の係数は負になるため符号付き型を用いる。

拡張 Euclid により $O(\log m)$。

#### 実装・検証

- [実装](../../math/inv-mod.hpp)
- [Verify: elementary.cpp](../../tests/unit/math/elementary.cpp)
