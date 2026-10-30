## ビット演算補助

`Nyaan` 名前空間に `popcnt`, `lsb` / `ctz`, `msb`, `gbit`, `sbit`, `PW`, `MSK` を定義する。

`lsb/ctz(0)` は 64、`msb(0)` は -1。`gbit(a,i)` はビット取得、`sbit(a,i,b)` は設定。`PW(n)` は `1LL<<n`、`MSK(n)` は下位 n ビットのマスク。

`u64` などを先に定義する必要があり、通常は `template.hpp` 経由で使う。シフト量は型の幅内とし、符号付き左シフトの範囲にも注意する。各操作 $O(1)$。

#### 実装・検証

- [実装](../../template/bitop.hpp)
- [関連検証（間接使用）: verify-aoj-alds-14-c.test.cpp](../../verify/verify-aoj-alds/verify-aoj-alds-14-c.test.cpp)
- [関連検証（間接使用）: aoj-cgl-1-a.test.cpp](../../verify/verify-aoj-cgl/aoj-cgl-1-a.test.cpp)
- [関連検証（間接使用）: aoj-cgl-1-b.test.cpp](../../verify/verify-aoj-cgl/aoj-cgl-1-b.test.cpp)
