## 多項式補間

`PolynomialInterpolation(xs, ys)` は $f(xs[i])=ys[i]$ を満たす次数が点数未満の多項式を、低次順の係数列で返す。

`xs`, `ys` は同じ非零の長さにし、`xs` の要素は係数体上で全て相異なる必要がある。点の差を逆元として使うので、同じ点に同じ値を渡した場合でも重複点は許されない。

積の木で $Q(x)=\prod_i(x-xs[i])$ を作り、$ys[i]/Q'(xs[i])$ を重みとして補間する。FPS の多項式積・除算と多点評価を利用する。

点数 $N$ に対して時間 $O(N\log^2 N)$、領域 $O(N\log N)$。

#### 実装・検証

- [実装](../../fps/polynomial-interpolation.hpp)
- [Verify: evaluation.cpp](../../tests/unit/fps/evaluation.cpp)
