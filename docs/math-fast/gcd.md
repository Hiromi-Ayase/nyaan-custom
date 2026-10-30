## 二進 GCD

シフトと減算を用いて非負整数の最大公約数を求める。

- `BinaryGCDImpl::binary_gcd(a, b)` は符号なし 64 bit 版、同名前空間の `binary_gcd128(a, b)` は符号なし 128 bit 版。
- グローバルな `binary_gcd(a, b)`、`binary_gcd128(a, b)` は符号付き整数を受け取り、絶対値の GCD を返す。
- 片方が `0` なら他方の絶対値、両方が `0` なら `0`。

符号付き型の最小値は絶対値を同じ型で表せないため対象外。内部の末尾ゼロ数計算には非零の値を渡す。ワード演算の回数は $O(\log \max(|a|,|b|))$。

#### 実装・検証

- [実装](../../math-fast/gcd.hpp)
- [検証: internal-math.test.cpp](../../verify/verify-unit-test/internal-math.test.cpp)
- [検証: math-fast-2.test.cpp](../../verify/verify-unit-test/math-fast-2.test.cpp)
- [検証: math-fast.test.cpp](../../verify/verify-unit-test/math-fast.test.cpp)
