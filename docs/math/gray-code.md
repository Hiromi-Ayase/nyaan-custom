## Gray code の列挙

`gray_code(n)` は `i ^ (i>>1)` を `i=0,...,2^n-1` について返す。隣り合う値は一ビットだけ異なる。

n は非負で、`1<<n` が符号付き int に収まり配列を確保できる範囲とする。n=0 の結果は `{0}`。時間・領域 $O(2^n)$。

#### 実装・検証

- [実装](../../math/gray-code.hpp)
- [Verify: affine-and-gray.cpp](../../tests/unit/math/affine-and-gray.cpp)
