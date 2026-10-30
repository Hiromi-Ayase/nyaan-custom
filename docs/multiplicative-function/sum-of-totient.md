## Euler の φ 関数の累積和

`sum_of_totient<T>(N)` は $\sum_{i=1}^N\varphi(i)$ を `T` で返す。`N` は非負整数で、`N = 0` なら `0`、`N = 1` なら `1`。

商 `floor(N/i)` を圧縮して素数の個数と和をふるい、素数冪の寄与を再帰的に足す。全ての整数の φ を保持する必要はない。

係数型には整数または modint などの加減乗除が必要。整数では途中の二乗を含めてオーバーフローしない型を選び、modint では `2` での除算が可能な法を使う。商の表は $O(\sqrt N)$ 領域で、時間は商のふるいと素数冪の列挙に依存する。

#### 実装・検証

- [実装](../../multiplicative-function/sum-of-totient.hpp)
- [検証: sum-of-mf.test.cpp](../../verify/verify-unit-test/sum-of-mf.test.cpp)
- [検証: yosupo-sum-of-totient.test.cpp](../../verify/verify-yosupo-math/yosupo-sum-of-totient.test.cpp)
