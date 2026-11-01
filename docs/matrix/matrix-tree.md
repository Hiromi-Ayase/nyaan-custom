## 行列木定理

`MatrixTree<T>(n)` は **`n+1` 頂点**の無向グラフの全域木を数える。頂点番号は `0..n`、内部には最後の頂点を除いた `n` 次 Laplacian 行列を保持する。コンストラクタには `n > 0` が必要。

- `add(i, j, x)` で重み `x` の無向辺を追加する。多重辺は加算される。
- `calc()` は全ての全域木について辺重みの積を足した値を返す。全ての辺を `1` にすれば全域木の個数。
- `get()` で内部の小行列を取得する。

係数 `T` は逆元を使える体とする。行列式計算は $O(n^3)$、領域 $O(n^2)$。このヘッダはFPSや多項式補間に依存しない。

多項式の辺重みを扱う場合は、[多項式版の行列木定理](polynomial-matrix-tree.md)を使う。以前の `MatrixTree<FormalPowerSeries<mint>>` は `PolynomialMatrixTree<mint>` に置き換える。

#### 実装・検証

- [実装](../../matrix/matrix-tree.hpp)
- [Verify: tree-count.cpp](../../tests/unit/matrix/tree-count.cpp)
