## Gauss の消去法

`GaussElimination(a, pivot_end = -1, diagonalize = false)` は行列 `a` を破壊的に掃き出し、`pair<int, T>` で階数と行列式用の値を返す。

`pivot_end` はピボットに使う列の終端（半開区間 `[0, pivot_end)`）。省略すると全列を使う。拡大係数行列では右辺の列を除外する。`diagonalize = true` ならピボットを `1` にし、上下の行からその列を消去する。偽なら下側のみを消去する。

返り値の第 2 要素を行列式として使うのは、正方行列の全列を処理した場合。係数は非零要素で割れる体を仮定する。浮動小数点の許容誤差は扱わない。空行列は `{0, 1}`。

$H\times W$ 行列に対して時間 $O(HW\min(H,W))$、行列以外の領域は $O(1)$。

#### 実装・検証

- [実装](../../matrix/gauss-elimination.hpp)
- [検証: gauss-elimination.test.cpp](../../verify/verify-unit-test/gauss-elimination.test.cpp)
- [検証: inverse-matrix.test.cpp](../../verify/verify-unit-test/inverse-matrix.test.cpp)
- [検証: yosupo-linear-equation-2.test.cpp](../../verify/verify-yosupo-math/yosupo-linear-equation-2.test.cpp)
