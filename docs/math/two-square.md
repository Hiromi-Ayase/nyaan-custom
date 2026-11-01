## 二平方和の整数解

`two_square(N)` は `x*x+y*y=N` を満たす非負整数の組を辞書順で返す。交換した組も別に返す。N<0 は空、N=0 は `{(0,0)}`。

`solve_norm_equation(N)` は偏角 `[0,90°)` の Gauss 整数による解。素数・素数冪用の下位関数もあり、素数 p に対する解なしは `(-1,-1)`。

素因数分解と Gauss 整数の積を使用する。時間は因数分解と出力解数に依存し、結果整理に $O(k\log k)$。内部の座標演算は主に 128 bit。

#### 実装・検証

- [実装](../../math/two-square.hpp)
- [Verify: gaussian.cpp](../../tests/unit/math/gaussian.cpp)
