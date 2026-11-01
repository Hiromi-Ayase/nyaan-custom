## Stirling 行列の作用

第二種 Stirling 数 $S(i,j)$ を成分とする下三角行列を、長さ $N$ のベクトルへ作用させる。

- `stirling_matrix(a, rev = false)` は $b_i=\sum_{j=0}^i S(i,j)a_j$。
- `stirling_matrix_trans(a, rev = false)` は転置行列の作用 $b_i=\sum_{j=i}^{N-1}S(j,i)a_j$。
- `rev = true` はそれぞれの逆変換。逆行列の係数には符号付き第一種 Stirling 数が現れる。

空入力には空配列を返す。指数関数への代入、多点評価・補間、Pascal 行列の作用を組み合わせ、行列そのものは構築しない。必要な階乗と点の差が可逆な体と FPS の積のバックエンドを使う。

時間 $O(N\log^2 N)$、領域 $O(N\log N)$。

#### 実装・検証

- [実装](../../fps/stirling-matrix.hpp)
- [Verify: combinatorial-transforms.cpp](../../tests/unit/fps/combinatorial-transforms.cpp)
