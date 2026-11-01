## 有理数

`RationalBase<T,U>(numerator,denominator)` は既約化し分母を正にした有理数。`Rational` と `Fraction` は T=long long、比較用 U=__int128_t の別名。

加減乗除・比較・`inverse()`・非負指数 `pow(k)` を提供する。分母 0 と零の逆元は禁止。`raw(x,y)` は正規化しない内部向け生成で、0 分母も通すため通常演算にはそのまま渡さない。

`to_mint(mod)` は分母が mod と互いに素のときの剰余表現。四則演算の中間積は T のままで、比較だけ U を使う。整数型版では約分前のオーバーフローを避ける。

#### 実装・検証

- [実装](../../math/rational.hpp)
- [Verify: rational.cpp](../../tests/unit/math/rational.cpp)
