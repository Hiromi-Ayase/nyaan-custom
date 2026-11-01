## 多変数の巡回畳み込み

`multivariate_circular_convolution(f,g,base)` は各変数について $x_i^{base_i}=1$ とした多項式積を返す。

配列長は `product(base)` とし、第 0 変数の指数が最も速く変わる混合基数順に係数を並べる。各 `base[i]` は正。積と素数探索の途中計算が `int` に収まる範囲で使用する。

各軸の長さの根を持つ 3 個の素数を探索し、Chirp Z-transform による多次元変換を行って CRT で元の係数の法へ戻す。FPS の積のバックエンドを用意する。CRT で復元する非負整数としての係数が、選んだ 3 素数の積未満である必要がある。

全要素数を $N$ とすると、時間は素数探索と各軸の変換の費用（高速な畳み込みならおおむね $O(N\sum_i\log base_i)$）、領域は配列と変換用の作業領域に依存する。内部で専用の動的 modint の法を変更する。

#### 実装・検証

- [実装](../../ntt/multivariate-circular-convolution.hpp)
- [Verify: multidimensional.cpp](../../tests/unit/ntt/multidimensional.cpp)
