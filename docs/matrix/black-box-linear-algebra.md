## 行列ベクトル積を用いる線形代数

行列ベクトル積から Krylov 列を作り、乱択した射影と Berlekamp–Massey 法で最小多項式を推定する。

- `ModMatrix<mint>(n)` は密行列、`SparseMatrix<mint>(n)` は行ごとの疎行列。`add(i, j, x)` で要素を加え、`A * b` でベクトルとの積を計算する。`apply(i, r)` は第 `i` 行の定数倍。
- `fast_pow<mint>(A, b, k)` は非負整数 `k` に対する `A^k b` を返す。
- `fast_det<mint>(A)` はランダムな行の倍率を使って行列式を求める。
- `BBLAImpl::mat_minpoly<mint>(A)` は漸化式側の係数順で多項式を返す。通常の低次順の多項式には反転して使う。

係数には素数を法とする有限体と FPS 演算のバックエンドが必要。乱択により確率的に誤る可能性があり、特に小さい体では注意する。最小多項式の 1 回の推定は $O(n)$ 回の行列ベクトル積と $O(n^2)$ の漸化式計算、領域 $O(n^2)$。

内部の `fast_linear_equation` は現実装で解の和の蓄積・返却が正しく行われていないため、連立方程式の解法として使用しない。公開される主要な関数は `fast_pow` と `fast_det`。

#### 実装・検証

- [実装](../../matrix/black-box-linear-algebra.hpp)
- [Verify: black-box.cpp](../../tests/unit/matrix/black-box.cpp)
