## Nimber と多項式基底の変換

`NimberToField<N>(proot)` は `1,proot,proot^2,...` を基底として、Nimber のビット表現と有限体の多項式係数表現を対応させる。

`nimber2field(n)` は係数ビット列、`field2nimber(bits)` は Nimber。proot の冪が全空間の基底を張ることが必要で、構築には復元付き XOR 掃き出しを使う。

基底の各ビットは対象の符号なし整数型の幅で生成し、64 bit 型の上位ビットも扱う。変換自体はビット幅に比例する。

#### 実装・検証

- [実装](../../math/nimber-to-field.hpp)
- [Verify: nimber.cpp](../../tests/unit/math/nimber.cpp)
