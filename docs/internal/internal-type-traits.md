## 内部用の型判定

`internal::is_broadly_integral_v<T>`, `is_broadly_signed_v<T>`, `is_broadly_unsigned_v<T>` は標準整数型に加えて `__int128_t` / `__uint128_t` を判定する。

`ENABLE_HAS_TYPE(name)` はネストした型、`ENABLE_HAS_VAR(name)` はメンバ名の存在を判定する `has_name<T>` と `has_name_v<T>` をマクロ展開位置に定義する。同じ名前で両方を展開すると衝突する。

C++17 の `void_t`・可変テンプレートを用いるコンパイル時の補助機能。

#### 実装・検証

- [実装](../../internal/internal-type-traits.hpp)
- [Verify: math-and-traits.cpp](../../tests/unit/internal/math-and-traits.cpp)
