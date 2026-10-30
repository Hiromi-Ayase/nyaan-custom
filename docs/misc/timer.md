## 経過時間の計測

`Timer timer` は構築時に計測開始する。`reset()` で起点を更新し、`elapsed()` または `timer()` でミリ秒単位の経過時間を `long long` として取得する。

`chrono::high_resolution_clock` を使用する。呼び出しは定数時間で、秒単位ではない。

#### 実装・検証

- [実装](../../misc/timer.hpp)
- [検証: bigint-gcd.test.cpp](../../verify/verify-unit-test/bigint-gcd.test.cpp)
- [検証: bitset-find-prev.test.cpp](../../verify/verify-unit-test/bitset-find-prev.test.cpp)
- [検証: composite-exp.test.cpp](../../verify/verify-unit-test/composite-exp.test.cpp)
