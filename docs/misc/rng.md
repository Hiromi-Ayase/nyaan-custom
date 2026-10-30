## 乱数生成補助

`rng()` は 64 bit の xorshift、`rng(l,r)` は閉区間、`randint(l,r)` は半開区間の整数を返す。剰余で範囲を縮めるため厳密な一様分布にはならない。

`rnd()` / `rnd(l,r)` は実数乱数、`randset(l,r,n)` は半開区間から重複なしに n 個選んだ昇順列、`randshf(v)` は配列を破壊的にシャッフルする。実数版は丸めで右端になる可能性がある。

`NyaanLocal` 定義時は固定シード、`RANDOMIZED_SEED` も定義すれば時刻由来に戻る。整数の区間幅がオーバーフローしないこと。暗号用途ではなく競技プログラミング向け。

#### 実装・検証

- [実装](../../misc/rng.hpp)
- [検証: aoj-1068.test.cpp](../../verify/verify-aoj-other/aoj-1068.test.cpp)
- [検証: aoj-2171-bigrational.test.cpp](../../verify/verify-aoj-other/aoj-2171-bigrational.test.cpp)
- [検証: arbitrary-modint.test.cpp](../../verify/verify-unit-test/arbitrary-modint.test.cpp)
