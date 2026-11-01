## 実行時に法を指定する modint

`ArbitraryModIntBase<id>` または別名 `ArbitraryModInt` を用い、値を作る前に `set_mod(m)` を呼ぶ。`1 <= m < 2^30`、偶数法も可能。

四則演算・比較・非負指数の `pow`・`inverse`・`get/get_mod` を提供する。同じ id の全オブジェクトで法を共有し、変更後は古い値を再利用しない。逆元には互いに素性が必要。

Barrett reduction により乗算は定数時間。逆元・累乗は対数時間。

#### 実装・検証

- [実装](../../modint/arbitrary-modint.hpp)
- [Verify: scalar.cpp](../../tests/unit/modint/scalar.cpp)
