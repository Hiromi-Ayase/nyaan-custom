## 八要素並列の modint

`mmint` は AVX2 の八つの 32 bit レーンに Montgomery 値を保持する。先に `mmint::set_mod<mint>()` で対応する Montgomery modint の定数を設定する。

整数を受けるコンストラクタは raw なレーンの設定。通常整数列は `itom` で Montgomery 化し、`mtoi` で戻す。`+,-,*` はレーンごとの演算、`operator[]` は内部値。

等値演算は内部ビット列の比較で、同じ剰余でも冗長表現が異なれば一致しない。定数は static で共有する。AVX2 対応 CPU が必要。

#### 実装・検証

- [実装](../../modint/vectorize-modint.hpp)
- [Verify: simd.cpp](../../tests/unit/modint/simd.cpp)
