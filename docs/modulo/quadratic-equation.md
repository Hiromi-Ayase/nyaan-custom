## 有限体上の二次方程式

`QuadraticEquation(a, b, c)` は $ax^2+bx+c=0$ の根を `vector<mint>` で返す。係数には奇素数を法とする modint を使う。

`a = 0, b != 0` なら一次方程式として 1 根、`a = b = 0, c != 0` なら空配列。全ての係数が `0` の場合は全ての値が解になるため、実装では assertion で除外される。

平方根の計算には `mod_sqrt` を使う。重根なら1根、異なる根を持つなら2根を返す。返り値の整列は保証しない。

主な計算量は剰余平方根と逆元の計算に依存する。

#### 実装・検証

- [実装](../../modulo/quadratic-equation.hpp)
- [Verify: roots.cpp](../../tests/unit/modulo/roots.cpp)
