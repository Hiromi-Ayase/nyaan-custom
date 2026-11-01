## Montgomery modint（固定法）

`LazyMontgomeryModInt<mod>` は奇数かつ `mod < 2^30` の法を Montgomery 表現で扱う。通常の四則演算・比較・`pow`・`inverse`・入出力に対応する。

`get()` で通常の剰余を取得する。公開メンバ a は通常の剰余ではなく内部表現。逆元には法との互いに素性が必要で、法が素数である必要はない。

加減乗算 $O(1)$、非負指数の累乗 $O(\log n)$、逆元 $O(\log mod)$。

#### 実装・検証

- [実装](../../modint/montgomery-modint.hpp)
- [Verify: scalar.cpp](../../tests/unit/modint/scalar.cpp)
