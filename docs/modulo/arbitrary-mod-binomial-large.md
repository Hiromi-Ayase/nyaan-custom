## 大きい法に対応した二項係数

`arbitrary_mod_binomial(mod)` を構築し、`C(n, r)` で二項係数を法 `mod` で求める。`1 <= mod < 2^30`、`0 <= n <= 10^18` を基本の範囲とし、`r < 0`, `n < 0`, `r > n` は `0`。法 `1` の結果も `0`。

法を素数冪に分解し、各剰余を CRT で合成する。小さい素数や素数冪は階乗表、大きい素数の因子は `simd_prime_binomial` のブロック階乗表を使う。大きい素数の経路には AVX2 が必要。

素数冪 `p^q` の `q >= 2` の経路では、表を約 2000 万要素で打ち切る。この素数冪が表の上限を超える場合、`n <= 20000000` など、参照する全ての剰余が表に収まる条件が別途必要。法だけを満たせば任意の `n` を処理できるわけではない。

前計算の時間・領域は法の因数と表サイズに依存し、大きい素数の表作成も相応の時間を要する。前計算後は各素数について $O(\log_p n)$ 桁を処理する。`arbitrary-mod-binomial.hpp` と同名の型を定義するため併用しない。

#### 実装・検証

- [実装](../../modulo/arbitrary-mod-binomial-large.hpp)
- [検証: yosupo-binomial-coefficient-large.test.cpp](../../verify/verify-yosupo-math/yosupo-binomial-coefficient-large.test.cpp)
