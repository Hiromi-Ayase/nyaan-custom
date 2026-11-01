## 指数関数への代入と逆変換

`composite_exp(f, c = 1, deg = -1)` は有限多項式 $f$ に対して $f(\exp(cx))\bmod x^{deg}$ を返す。`deg` の省略時は `f.size()`。`c != 0` とし、空入力の返り値は空配列。

`inverse_of_composite_exp(f, c = 1)` は長さ $N$ の級数を $\sum_{k=0}^{N-1}a_k\exp(ckx)\bmod x^N$ と表した係数 `a[0..N)` を返す。こちらも `c != 0` が必要で、点 `0,c,...,(N-1)c` が相異なる体を使う。

積の木と有理式の合成を利用する。階乗や差の逆元が必要なので、素数の法では必要な次数を法未満にする。FPS の多項式積のバックエンドも必要。

多項式積の時間を $M(N)$ とすると、同程度の入力長・出力長では時間 $O(M(N)\log N)$、積の木の領域は $O(N\log N)$。

#### 実装・検証

- [実装](../../fps/composite-exp.hpp)
- [Verify: combinatorial-transforms.cpp](../../tests/unit/fps/combinatorial-transforms.cpp)
