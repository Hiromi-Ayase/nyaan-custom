## 固定サイズの行列

`Matrix<T, H, W>` は `array` に保持する固定サイズの行列。デフォルト構築で全要素を `0` にし、`height()`, `width()`, `operator[]` を提供する。

同じ形の加減算、正方行列の積・非負整数乗、`I()` による単位行列を扱う。`determinant(n = -1)` は左上 `n` 次の行列式で、省略時は実装の既定サイズを使う。正方行列で `0 <= n <= H` の範囲を指定する。

行列式は非零要素の逆元がある係数体を仮定し、浮動小数点向けのピボット安定化はしない。$n$ 次正方行列の積・行列式は $O(n^3)$、累乗は $O(n^3\log k)$、領域は $O(HW)$。`matrix.hpp` の同名テンプレートと併用しない。

#### 実装・検証

- [実装](../../matrix/matrix-fast.hpp)
- [検証: template.test.cpp](../../verify/verify-unit-test/template.test.cpp)
- [検証: yosupo-determinant-matrixlib.test.cpp](../../verify/verify-yosupo-math/yosupo-determinant-matrixlib.test.cpp)
- [検証: yosupo-pow-of-matrix-2.test.cpp](../../verify/verify-yosupo-math/yosupo-pow-of-matrix-2.test.cpp)
