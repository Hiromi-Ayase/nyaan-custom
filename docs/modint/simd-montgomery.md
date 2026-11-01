## SIMD Montgomery 演算

`montgomery_mul/add/sub_128` と `_256` はそれぞれ四つ・八つの 32 bit レーンを並列処理する。通常整数を直接受ける汎用 modint ではなく、Montgomery 表現と前計算済みの定数を渡す低水準関数。

r は法の 2^32 に対する逆元、m1 は法、m2 は法の二倍、m0 は零を各レーンに入れたもの。値域は LazyMontgomeryModInt の規約に合わせる。

128 bit 版は SSE4.2、256 bit 版は AVX2 を使い、対応 CPU が必要。各呼び出しは定数個の SIMD 命令。

#### 実装・検証

- [実装](../../modint/simd-montgomery.hpp)
- [Verify: simd.cpp](../../tests/unit/modint/simd.cpp)
