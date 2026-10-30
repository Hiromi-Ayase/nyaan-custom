## 動的サイズの行列

`Matrix<T>` は `vector<vector<T>>` の行列。`Matrix(n, m)` は零行列、`Matrix(n)` は正方零行列、`Matrix::I(n)` は単位行列を作る。

- `H()`, `W()`, `size()` で行数・列数・行数を取得し、`A` または `operator[]` で要素にアクセスする。
- `+`, `-` は同じ形の行列、`*` は内側の次元が一致する行列に使う。
- `^ k` は正方行列の非負整数乗。
- `inverse()` は逆行列を返し、特異なら空の行列を返す。`determinant()` は行列式を返す。

加減乗算は環上で使えるが、逆行列・行列式の消去法は非零要素で割れる係数体が必要。浮動小数点向けの誤差判定や最大絶対値によるピボット選択はしない。空行列に `W()` を呼ばない。

$h\times k$ と $k\times w$ の積は $O(hkw)$。$n$ 次正方行列の逆行列・行列式は $O(n^3)$、累乗は $O(n^3\log k)$。`matrix-fast.hpp` の同名テンプレートとは同時に利用しない。

#### 実装・検証

- [実装](../../matrix/matrix.hpp)
- [検証: bigint-gcd.test.cpp](../../verify/verify-unit-test/bigint-gcd.test.cpp)
- [検証: debug.test.cpp](../../verify/verify-unit-test/debug.test.cpp)
- [検証: gauss-elimination.test.cpp](../../verify/verify-unit-test/gauss-elimination.test.cpp)
