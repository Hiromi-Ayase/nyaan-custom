## 異なる非空部分列の個数

`number_of_subsequences<Container,mint>(s)` は順序を保って要素を選んでできる、異なる非空部分列の個数を返す。同じ内容を作る添字の選び方は重複して数えない。

各要素の直前の寄与をハッシュ表で管理する。空入力の結果は 0。`mint` は零・一・加減算を持つ型、要素型は `UnerasableHashMap` が扱えるキー型とする。

期待時間 $O(n)$、領域は異なる要素数に比例する。

#### 実装・検証

- [実装](../../string/number-of-subsequences.hpp)
- [検証: yosupo-number-of-subsequences.test.cpp](../../verify/verify-yosupo-string/yosupo-number-of-subsequences.test.cpp)
