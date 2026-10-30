## 素数の列挙

`prime_enumerate(N)` は `N` 以下の素数を昇順の `vector<int>` で返す。`N < 2` なら空。`N` は非負とする。

2 と 3 の倍数を省いた篩を使う。時間 $O(N\log\log N)$、篩の領域 $O(N)$ ビットと出力領域を使う。

#### 実装・検証

- [実装](../../prime/prime-enumerate.hpp)
- [検証: garner-bigint.test.cpp](../../verify/verify-unit-test/garner-bigint.test.cpp)
- [検証: primitive-root.test.cpp](../../verify/verify-unit-test/primitive-root.test.cpp)
- [検証: yosupo-prime-table.test.cpp](../../verify/verify-yosupo-math/yosupo-prime-table.test.cpp)
