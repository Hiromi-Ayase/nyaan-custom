## Nimber と多項式基底の変換

`NimberToField<N>(proot)` は `1,proot,proot^2,...` を基底として、Nimber のビット表現と有限体の多項式係数表現を対応させる。

`nimber2field(n)` は係数ビット列、`field2nimber(bits)` は Nimber。proot の冪が全空間の基底を張ることが必要で、構築には復元付き XOR 掃き出しを使う。

現在のコンストラクタには `1 << i` という int 幅のシフトがあるため、32 bit 以上の位置を含む型では修正が必要。変換自体はビット幅に比例する。

#### 実装・検証

- [実装](../../math/nimber-to-field.hpp)
- [検証: nimber-to-field.test.cpp](../../verify/verify-unit-test/nimber-to-field.test.cpp)
