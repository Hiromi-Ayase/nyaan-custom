## Run（極大周期区間）の列挙

`run_enumerate(s)` は `(p,l,r)` の列を返す。`s[l:r]` は最小周期 `p` を持ち、長さが `2*p` 以上で、同じ周期のまま左右へ延長できない区間。

文字列や配列に適用でき、区間は半開。同じ区間の重複は除去される。返却順は周期順を基本とし、開始位置だけでソートされた列ではない。

分割統治・Z algorithm で候補を作り、ソートと集合で整理する。保守的な上界は時間 $O(n\log^2 n)$、候補を含む領域 $O(n\log n)$。

#### 実装・検証

- [実装](../../string/run-enumerate.hpp)
- [検証: yosupo-run-enumerate.test.cpp](../../verify/verify-yosupo-string/yosupo-run-enumerate.test.cpp)
