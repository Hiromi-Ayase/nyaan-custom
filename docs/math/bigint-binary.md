## 二進表現の多倍長整数

`BinaryBigIntImpl::BinaryBigInt(s,16)` は十六進文字列から符号付き多倍長整数を構築する。加減乗算・比較・符号反転・非負ビット数の `<<=/>>=`、`ctz()`、`gcd`、`to_hex()` を提供する。一般の除算・剰余はない。

符号と 32 bit 桁を分けて保存するので、負数の右シフトは算術シフトではなく絶対値のシフト。入力は非空の有効な十六進表現とする。

加減算・シフトは桁数に比例し、乗算は規模に応じ畳み込みを用いる。内部桁の正規化に依存するため、raw な配列や neg を直接変更しない。

#### 実装・検証

- [実装](../../math/bigint-binary.hpp)
- [検証: bigint-gcd.test.cpp](../../verify/verify-unit-test/bigint-gcd.test.cpp)
- [検証: yosupo-addition-of-hex.test.cpp](../../verify/verify-yosupo-math/yosupo-addition-of-hex.test.cpp)
- [検証: yosupo-multiplication-of-hex.test.cpp](../../verify/verify-yosupo-math/yosupo-multiplication-of-hex.test.cpp)
