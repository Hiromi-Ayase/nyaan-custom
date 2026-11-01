## 3 つの NTT による任意法の畳み込み

`ArbitraryNTT` 名前空間で、3 つの NTT 向け素数の結果を CRT で合成する。

- `multiply(a,b,mod)` は整数配列を受け取り `vector<int>` の剰余を返す。`mod > 0` とし、入力はあらかじめ非負の代表元へ正規化する。
- modint 配列の `multiply(a,b)` は `get()` と `get_mod()` を使う。
- `multiply_u128(a,b)` は非負整数の畳み込みを `__uint128_t` の配列で返す。

どの版も両入力を非空にする。復元する整数係数は `167772161 * 469762049 * 754974721` 未満である必要がある。任意法へ落とす場合も、CRT 前の整数としての係数にこの上限がある。`multiply_u128` の小さい入力向け経路では積に 64 bit 整数を使うため、その途中計算にも収まる必要がある。

変換長は結果長を切り上げた 2 冪で、最大 $2^{24}$。時間 $O(N\log N)$、領域 $O(N)$。

#### 実装・検証

- [実装](../../ntt/arbitrary-ntt.hpp)
- [Verify: arbitrary-modulus.cpp](../../tests/unit/ntt/arbitrary-modulus.cpp)
