## 多倍長整数の GCD・LCM

`gcd(a,b)` は bigint の非負最大公約数。符号を除いて二進的な減算と因子除去を行い、小さくなると固定幅の GCD へ切り替える。

`lcm(a,b)` は `a/gcd(a,b)*b` として計算する。負入力では符号が残り、両方 0 だと零除算になるので、通常は正の入力を渡す。

時間は桁数と減算・因子除去の回数に依存する。結果が機械整数に収まらない場合も bigint として保持する。

#### 実装・検証

- [実装](../../math/bigint-gcd.hpp)
- [検証: bigint-gcd.test.cpp](../../verify/verify-unit-test/bigint-gcd.test.cpp)
