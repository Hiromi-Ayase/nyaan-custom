## 行列の特性多項式

`CharacteristicPolynomial(a)` は $\det(A-xI)$ の係数を低次から順に返す。$n$ 次正方行列なら長さは `n+1`、最高次係数は $(-1)^n$。よく使われる $\det(xI-A)$ とは偶奇による符号の違いがある。

空行列では `{1}`。行列をコピーして Hessenberg 形へ変換し、部分行列の多項式を順に求める。係数は非零要素で割れる体が必要で、任意の合成数の法には対応しない。

時間 $O(n^3)$、領域 $O(n^2)$。ファイル名の `characteristric` は実装の綴りに合わせる。

#### 実装・検証

- [実装](../../matrix/characteristric-polynomial.hpp)
- [Verify: dynamic.cpp](../../tests/unit/matrix/dynamic.cpp)
