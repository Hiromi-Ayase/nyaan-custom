## 実行時法の Montgomery modint

`ArbitraryLazyMontgomeryModInt<id>` は 32 bit、`ArbitraryLazyMontgomeryModInt64bit<id>` は 64 bit の内部表現を使う。最初に `set_mod(m)` する。

法は正の奇数で、前者は 2^30 未満、後者は 2^62 未満。四則演算・比較・累乗・逆元・get/get_mod を提供する。逆元には法との互いに素性が必要。

法は同じ型の全値で共有され、途中で変えると既存値の解釈が変わる。内部 a を通常の剰余と混同しない。64 bit 版は 128 bit 乗算に依存する。

#### 実装・検証

- [実装](../../modint/arbitrary-montgomery-modint.hpp)
- [検証: arbitrary-modint.test.cpp](../../verify/verify-unit-test/arbitrary-modint.test.cpp)
- [検証: ntt-64bit.test.cpp](../../verify/verify-unit-test/ntt-64bit.test.cpp)
- [検証: yosupo-convolution-arbitraryntt-arbitraryprimemodint.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-arbitraryntt-arbitraryprimemodint.test.cpp)
