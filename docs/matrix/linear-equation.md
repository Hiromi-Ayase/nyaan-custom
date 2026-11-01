## 連立一次方程式の解空間

`LinearEquation(a, b)` は `a*x = b` の解を `vector<vector<T>>` で返す。入力はコピーされ、元の配列は変化しない。

- 解がなければ空配列。
- 解があれば先頭が特殊解、以降が同次方程式 `a*x = 0` の基底。
- 全ての解は「特殊解 + 基底の任意の線形結合」で表せる。一意解なら要素は 1 個。

`a` は非空の長方形行列、`b.size()` は行数に合わせる。係数は非零要素で割れる体で、浮動小数点の誤差判定は行わない。消去の時間は $O(HW\min(H,W))$、解空間の出力には最大 $O(W^2)$ の領域が必要。

#### 実装・検証

- [実装](../../matrix/linear-equation.hpp)
- [Verify: linear-algebra.cpp](../../tests/unit/matrix/linear-algebra.cpp)
