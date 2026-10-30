## 多倍長整数の十六進変換

`HtoB(s)` は十六進文字列を bigint に変換し、`BtoH(x)` は bigint を大文字の十六進文字列へ変換する。負号に対応し、入力の英字は大小どちらも使える。`0x` 接頭辞は付けない。

入力は非空の有効な数字列とし、負の零表現は避ける。分割統治と 16 の冪のキャッシュを使うため、時間は桁数と bigint の乗除算に依存する。

#### 実装・検証

- [実装](../../math/bigint-to-hex.hpp)
- [検証: bigint-gcd.test.cpp](../../verify/verify-unit-test/bigint-gcd.test.cpp)
- [検証: yosupo-division-of-hex.test.cpp](../../verify/verify-yosupo-math/yosupo-division-of-hex.test.cpp)
