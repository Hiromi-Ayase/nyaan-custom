## 逆行列

`inverse_matrix(a)` は正方行列 `a` の逆行列を返す。特異で逆行列がなければ空配列を返す。引数は変更しない。

入力は非空の正方行列。係数は非零要素の逆元を持つ体を仮定し、合成数を法とする modint はそのままでは使えない。浮動小数点に対する許容誤差や数値安定性のためのピボット選択は含まない。

単位行列を右に連結した拡大係数行列を掃き出す。$n$ 次行列に対して時間 $O(n^3)$、追加領域 $O(n^2)$。

#### 実装・検証

- [実装](../../matrix/inverse-matrix.hpp)
- [検証: inverse-matrix.test.cpp](../../verify/verify-unit-test/inverse-matrix.test.cpp)
- [検証: yosupo-inverse-matrix.test.cpp](../../verify/verify-yosupo-math/yosupo-inverse-matrix.test.cpp)
