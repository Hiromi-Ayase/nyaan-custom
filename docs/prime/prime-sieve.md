## 素数判定表

`prime_sieve(N)` は添字が素数なら真となる `vector<bool>` を返す。非負の `N` を渡す。0 と 1 は偽。

通常の長さは `N+1` だが、`N==0` でも 0 と 1 を格納するため長さ 2。時間 $O(N\log\log N)$、領域 $O(N)$ ビット。内部で `i*i` を `int` として計算する。

#### 実装・検証

- [実装](../../prime/prime-sieve.hpp)
- [検証: primality-test.test.cpp](../../verify/verify-unit-test/primality-test.test.cpp)
- [検証: yosupo-prime-enumerate-sieve.test.cpp](../../verify/verify-yosupo-math/yosupo-prime-enumerate-sieve.test.cpp)
