## 64 bit 素数の原始根

`primitive_root_ll(p)` は素数 p の原始根を一つ返す。p=2 の場合は 1。

p-1 を素因数分解し、候補 g について各素因数 q に対する `g^((p-1)/q) != 1 mod p` を確認する。p の素数判定は行わないので呼び出し側で保証する。

時間は素因数分解と試す候補数に依存する。modpow の中間積は `__int128_t`。候補変数自体は int である。

#### 実装・検証

- [実装](../../math/primitive-root-ll.hpp)
- [検証: yosupo-primitive-root.test.cpp](../../verify/verify-yosupo-math/yosupo-primitive-root.test.cpp)
