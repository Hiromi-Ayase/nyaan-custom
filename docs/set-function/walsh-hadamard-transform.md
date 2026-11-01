## Walsh–Hadamard 変換

`walsh_hadamard_transform(f,inverse=false)` は XOR 畳み込み用の変換を破壊的に行う。正の 2 冪長の配列を渡す。

`inverse=true` では同じ蝶演算の後に長さで割る。整数型は整数除算、その他は `T(1)/T(size)` の乗算なので、対応する逆元が必要。通常変換は加減算だけで計算する。

時間 $O(N\log N)$、追加領域 $O(1)$。

#### 実装・検証

- [実装](../../set-function/walsh-hadamard-transform.hpp)
- [Verify: transforms.cpp](../../tests/unit/set-function/transforms.cpp)
