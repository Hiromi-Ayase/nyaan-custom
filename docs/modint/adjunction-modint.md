## 平方根を添加した係数型

`Adjunction<mint,B>(a,b)` は `a+b*sqrt(B)` を表す。四則演算・比較・非負指数 `pow(e)` を提供する。

`inverse()` は共役を `a*a-B*b*b` で割る。したがってこの norm が mint 上で可逆であることが必要。B が平方剰余の場合など、非零の要素でも逆元がないことがある。

加減乗算は定数回の mint 演算。拡大体として使うには基礎体と B の選択条件を満たすこと。

#### 実装・検証

- [実装](../../modint/adjunction-modint.hpp)
- [検証: yuki-2883.test.cpp](../../verify/verify-yuki/yuki-2883.test.cpp)
