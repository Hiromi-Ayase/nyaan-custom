## Schönhage–Strassen 型の多項式積

`Schoenhage_Strassen_radix2<T>().multiply(a,b)` は係数環上で多項式積を計算し、`pair<vector<T>, int>` を返す。

返り値を `(c, k)` とすると、`c` は通常の畳み込みの **`2^k` 倍**。逆変換で正規化を行わないため、正しい積を得るには各成分を `2^k` で割る必要がある。係数体なら逆元を掛け、整数なら中間値も含めた型の範囲と割り算を確認する。標数 `2` ではこの復元はできない。

両入力は非空とする。係数型は零・加減乗算を提供し、内部で `memcpy` を使うのでバイトコピーできる型が必要。

多項式剰余環でシフトを回転因子として扱い、再帰的に積を求める。時間は $O(N\log N\log\log N)$ 程度の環演算。作業領域をオブジェクトに保持するため、同じオブジェクトへの並行呼び出しはできない。

#### 実装・検証

- [実装](../../ntt/schoenhage-strassen-radix2.hpp)
- [検証: yosupo-convolution-schoenhage-radix2.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-schoenhage-radix2.test.cpp)
