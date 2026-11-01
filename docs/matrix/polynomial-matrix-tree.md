## 多項式の辺重みに対応した行列木定理

`PolynomialMatrixTree<mint>(n)` は `n+1` 頂点の無向グラフについて、全域木ごとの辺重みの積を足した多項式を返す。頂点番号は `0..n`、コンストラクタには `n > 0` を渡す。

- `add(i, j, f)` で `FormalPowerSeries<mint>` 型の重み `f` を持つ無向辺を追加する。多重辺は加算し、自己ループは全域木に寄与しない。
- `calc()` は全域木の重みの和を `FormalPowerSeries<mint>` で返す。末尾の零係数が残る場合がある。
- `get()` は最後の頂点を除いたLaplacianの小行列を返す。

係数の型 `mint` と、`ntt-friendly-fps.hpp` または `arbitrary-fps.hpp` を別途用意する。数値の辺重みだけでよい場合は [MatrixTree](matrix-tree.md) を使う。

多項式行列式を評価・補間で計算する。Laplacianの各行の最大次数を足した値を `D` とすると、行列式評価は $O((D+1)n^3)$。これに多項式評価と補間の費用が加わる。係数体で `0..D` の評価点が相異なることが必要。

#### 実装・検証

- [実装](../../matrix/polynomial-matrix-tree.hpp)
- [Verify: polynomial-tree-count.cpp](../../tests/unit/matrix/polynomial-tree-count.cpp)
