## 多項式で表される数列の累積和

`fualhuber(f, C)` は $g(n)=\sum_{j=0}^{n}f(j)$ を満たす多項式 $g$ の係数を返す。`f` は値の列ではなく、低次順の多項式係数。返り値の長さは `f.size()+1`。

入力は非空とし、`Binomial<mint>` と Bernoulli 数を使うため、必要な整数・階乗が可逆な体を用いる。内部で `N+4` までの逆階乗を参照するので、法は十分大きくする。

Bernoulli 数の指数型母関数と 1 回の畳み込みを利用する。高速な FPS 演算では時間 $O(N\log N)$、領域 $O(N)$。関数名の `fualhuber` は実装通りの綴り。

#### 実装・検証

- [実装](../../fps/fualhuber.hpp)
- [検証: yuki-2580.test.cpp](../../verify/verify-yuki/yuki-2580.test.cpp)
