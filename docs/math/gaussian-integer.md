## Gauss 整数

`Gaussian_Integer<T>(x,y)` は `x+y*i`。四則演算、剰余、`conj()`、`norm()`、非負指数 `pow(e)`、`gcd(a,b)` を提供する。

除算は複素数としての商を整数格子へ丸めたもの。剰余と合わせて Euclid 法に使う。ゼロ除算は禁止し、積・norm が T に収まる必要がある。

pair コンストラクタで `fi/se`、gcd で `trc` マクロを使うため、競技用テンプレートなどで先に定義する。累乗は $O(\log e)$ 回の乗算。

#### 実装・検証

- [実装](../../math/gaussian-integer.hpp)
- [検証: yosupo-gcd-of-gaussian-integer.test.cpp](../../verify/verify-yosupo-math/yosupo-gcd-of-gaussian-integer.test.cpp)
