## AVX2 による Gauss 消去法

`Gauss` 名前空間の Montgomery modint 用の消去法。AVX2 対応 CPU と、内部値 `.a`, `r`, `get_mod()` を持つ対応した 32 bit modint が必要。

- `GaussianElimination(m, LinearEquation = false)` は階数と行列式用の値を返す。真なら最後の列を右辺とみなし、ピボットを正規化して上下を消去する。
- `determinant(mat)` は非空正方行列の行列式。
- `LinearEquation(A, B)` は先頭が特殊解、以降が同次方程式の基底の配列を返す。解がなければ空配列。

入力は非空とし、行数と処理する列数を `4096` 以下に収める。方程式では右辺を追加するので変数数は最大 `4095`。係数は非零要素で割れる体が必要。

時間は $O(HW\min(H,W))$ の演算を SIMD で並列化する。約 64 MiB のグローバルな作業配列を共有し、並行・再入呼び出しには対応しない。入力の行列自体は変更しない。

#### 実装・検証

- [実装](../../modulo/gauss-elimination-fast.hpp)
- [検証: gauss-elimination.test.cpp](../../verify/verify-unit-test/gauss-elimination.test.cpp)
- [検証: yosupo-determinant.test.cpp](../../verify/verify-yosupo-math/yosupo-determinant.test.cpp)
- [検証: yosupo-linear-equation.test.cpp](../../verify/verify-yosupo-math/yosupo-linear-equation.test.cpp)
