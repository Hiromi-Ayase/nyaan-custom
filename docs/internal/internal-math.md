## 内部用の整数剰余演算

`internal::safe_mod(a,p)` は正の p に対し非負剰余を返す。`inv_gcd(a,p)` は `(gcd(a,p),x)` で `a*x ≡ gcd(a,p) mod p`。`inv(a,p)` は互いに素のときだけ使える逆元。

`modpow<T,U>(a,n,p)` は非負指数の累乗で、`U` に積が収まること。`crt(r,m)` は同じ長さの剰余・正の法から `(解, 法の最小公倍数)` を返し、矛盾時は `(0,0)`。合成後の法・中間積が型に収まる必要がある。

逆元は対数時間、累乗は $O(\log n)$、CRT は制約ごとに拡張 Euclid を行う。標準ヘッダを先に読み込む競技用テンプレートとの利用を想定する。

#### 実装・検証

- [実装](../../internal/internal-math.hpp)
- [Verify: math-and-traits.cpp](../../tests/unit/internal/math-and-traits.cpp)
