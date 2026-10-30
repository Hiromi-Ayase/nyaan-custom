## Pascal 行列の作用

長さ $N$ の縦ベクトルに二項係数の行列を掛ける。返り値の長さも $N$ で、空入力には空配列を返す。

- `pascal_matrix(a, rev = false)` は $b_i=\sum_{j=0}^i\binom ij a_j$。
- `pascal_matrix_trans(a, rev = false)` は転置行列の作用 $b_i=\sum_{j=i}^{N-1}\binom ji a_j$。
- `rev = true` はそれぞれの逆行列を作用させ、和の係数に $(-1)^{|i-j|}$ が付く。

階乗・逆階乗を掛けて通常の畳み込みへ帰着する。必要な階乗が可逆な体（十分大きい素数の modint など）と FPS の積のバックエンドを使う。

時間 $O(N\log N)$、領域 $O(N)$。行列そのものは構築しない。

#### 実装・検証

- [実装](../../fps/pascal-matrix.hpp)
- [関連検証（間接使用）: stirling-matrix.test.cpp](../../verify/verify-unit-test/stirling-matrix.test.cpp)
