## 平方因子を持たない整数の個数

`count_square_free(N)` は `1` 以上 `N` 以下で、どの素数の平方でも割り切れない整数の個数を `long long` で返す。`1` は数え、`N = 0` の結果は `0`。

$\sum_{d\le\sqrt N}\mu(d)\lfloor N/d^2\rfloor$ を、商が同じ区間でまとめて計算する。$N^{2/5}$ 程度までのメビウス関数の累積和を作り、それより大きい引数の累積和は再帰とキャッシュで求める。

入力は非負で、平方根や積の内部計算が整数型に収まる範囲。前計算の領域は $O(N^{2/5})$、これに商ごとのキャッシュを用いる。計算時間は前計算と再帰で訪れる商の個数に依存する。

#### 実装・検証

- [実装](../../multiplicative-function/count-square-free.hpp)
- [検証: yosupo-count-squarefrees.test.cpp](../../verify/verify-yosupo-math/yosupo-count-squarefrees.test.cpp)
