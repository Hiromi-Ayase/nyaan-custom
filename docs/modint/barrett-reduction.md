## Barrett reduction

`Barrett(m)` は正の int の法を前計算する。`quo(n)`, `rem(n)`, `quorem(n)` は符号なし 64 bit 入力の商・剰余・両者を返す。`pow(n,p)` は非負指数 p の modular power。

デフォルト構築のまま計算しない。商の返却型は long long なので、その範囲を超える商は対象外。`__uint128_t` の高位積を用い、商・剰余は定数時間、累乗は $O(\log p)$。

#### 実装・検証

- [実装](../../modint/barrett-reduction.hpp)
- [関連検証（間接使用）: arbitrary-modint.test.cpp](../../verify/verify-unit-test/arbitrary-modint.test.cpp)
- [関連検証（間接使用）: barrett-reduction.test.cpp](../../verify/verify-unit-test/barrett-reduction.test.cpp)
- [関連検証（間接使用）: garner-bigint.test.cpp](../../verify/verify-unit-test/garner-bigint.test.cpp)
