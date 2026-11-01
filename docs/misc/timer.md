## 経過時間の計測

`Timer timer` は構築時に計測開始する。`reset()` で起点を更新し、`elapsed()` または `timer()` でミリ秒単位の経過時間を `long long` として取得する。

`chrono::high_resolution_clock` を使用する。呼び出しは定数時間で、秒単位ではない。

#### 実装・検証

- [実装](../../misc/timer.hpp)
- [Verify: random-and-timer.cpp](../../tests/unit/misc/random-and-timer.cpp)
