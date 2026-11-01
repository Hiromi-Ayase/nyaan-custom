## 8 要素をまとめた Montgomery 演算

`vectorize_modint<mint>` は AVX2 の 256 bit レジスタで、8 個の剰余に同じ加減乗算を行う。`mint::r`、`mint::n2`、`mint::get_mod()` を使う Montgomery modint が必要。

- 整数、8 要素の `array<int, 8>`、8 個の整数、または `__m256i` から構築する。コンストラクタはビット列を設定し、通常の整数を自動的に Montgomery 表現へ変換しない。
- `itom(v)` で通常の剰余から Montgomery 表現へ、`mtoi(v)` で戻す。
- `at(i)` / `set(i, value)` は `0 <= i < 8` の内部値を読み書きする。
- `+`, `-`, `*` は各レーン独立の演算。

GCC の AVX2 指定を含み、AVX2 対応 CPU が必要。静的定数は型ごとに初期化されるので、演算途中で法を変更しない。1 回の演算は固定 8 要素に対して $O(1)$。

#### 実装・検証

- [実装](../../math-fast/vectorize-modint.hpp)
- [Verify: simd.cpp](../../tests/unit/modint/simd.cpp)
