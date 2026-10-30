## 任意の法での行列式

`determinant_arbitrary_mod(a)` は正方行列の行列式を返す。入力は値渡しで、空行列の行列式は `1`。

係数型には `.get()` で非負の整数代表元を取得できる modint を使う。通常の Gauss 消去で必要になる剰余の逆元を使わず、代表元の整数除算と行の交換・減算で消去するため、法が合成数でも計算できる。

$n$ 次行列、法 $m$ に対して時間は $O(n^3\log m)$ 以下、コピーを含む領域 $O(n^2)$。一般の整数型や浮動小数点型向けの関数ではない。

#### 実装・検証

- [実装](../../matrix/determinant-arbitrary-mod.hpp)
- [検証: yosupo-determinant-arbitrary-mod.test.cpp](../../verify/verify-yosupo-math/yosupo-determinant-arbitrary-mod.test.cpp)
