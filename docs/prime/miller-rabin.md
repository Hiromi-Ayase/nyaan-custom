## 64 bit 整数の素数判定

`is_prime(unsigned long long n)` は `n` の素数判定を返す。0 と 1 は偽、2 は真。

値域に応じて Montgomery 演算と `__uint128_t` を切り替え、64 bit 整数用の固定基底で Miller–Rabin 判定を行う。下位関数 `miller_rabin` に任意の基底を渡す場合、同じ判定保証があるとは限らない。

基底数は定数で、固定幅の乗算を $O(1)$ とすれば時間 $O(\log n)$。内部で専用 ID の動的 modint の法を変更する。

#### 実装・検証

- [実装](../../prime/miller-rabin.hpp)
- [検証: ntt-64bit.test.cpp](../../verify/verify-unit-test/ntt-64bit.test.cpp)
- [検証: primality-test.test.cpp](../../verify/verify-unit-test/primality-test.test.cpp)
- [検証: yosupo-primality-test-u64.test.cpp](../../verify/verify-yosupo-math/yosupo-primality-test-u64.test.cpp)
