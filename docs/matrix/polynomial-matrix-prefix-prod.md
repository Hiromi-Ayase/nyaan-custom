## 多項式行列の連続積

`polynomial_matrix_prod(m, k)` は多項式を各要素に持つ正方行列 $M(x)$ から、$M(k-1)M(k-2)\cdots M(0)$ を返す。引数は `Matrix<FormalPowerSeries<mint>>`、返り値は `Matrix<mint>`。積の順序に注意する。

`m` は非空の正方行列、`k` は非負整数。`k = 0` の結果は単位行列。FPS の積を提供するバックエンドを先に読み込む。係数体ではブロック幅と補間に使う階乗が可逆である必要があり、標数が小さすぎる場合には使えない。

ブロック単位の行列積を多項式の標本点シフトで構築し、連続する全ての行列を個別には生成しない。要素の最大次数を丸めた値を $d$ として、幅 $v$ を $dv^2\ge k$ となる 2 冪に選ぶ。時間・領域は行列サイズ、$d$、$v$ と多項式積の計算量に依存する。

#### 実装・検証

- [実装](../../matrix/polynomial-matrix-prefix-prod.hpp)
- [Verify: polynomial.cpp](../../tests/unit/matrix/polynomial.cpp)
