## GF(2) と Boolean 行列

`F2_Matrix<H_MAX, W_MAX>(h, w)` は固定容量の `bitset` 配列に実際の行数・列数を持たせた行列。`h <= H_MAX`, `w <= W_MAX` とし、範囲外のビットは `0` にする。

- `operator[]` で行のビット列へアクセスし、`I(n)` で単位行列を作る。
- `*` は XOR と AND による GF(2) の積。`and_or_product(a, b)` は OR と AND による Boolean 積。
- `sweep(wr = -1)` は先頭 `wr` 列（省略時は全列）をピボットに破壊的に掃き出し、階数を返す。
- `inverse()` は成功フラグと逆行列の組、`determinant()` は `0` または `1` を返す。

正方行列の逆行列・行列式は bitset を使った消去法。ビット列の処理はワード単位で並列化されるが、確保領域は実寸ではなくテンプレートの最大容量に依存する。現実装の `*=` は列数を更新しないため、結果の列数が変わる長方形の積には `*` を使う。GCC の bitset 拡張を使用する。

#### 実装・検証

- [実装](../../matrix/f2-matrix.hpp)
- [Verify: f2.cpp](../../tests/unit/matrix/f2.cpp)
