## 線形漸化式の推定

`BerlekampMassey(s)` は与えた数列の範囲に一致する最短の線形漸化式を返す。係数は体とし、消去時に現れる非零値で割れる必要がある。

返り値 `c` の先頭は `1`。`L = c.size()-1` とすると、$s[t]+c[1]s[t-1]+\cdots+c[L]s[t-L]=0$ を表す。通常の「過去の項の線形結合」として使うときは `c[1..L]` の符号を反転する。全て `0` の列や空列の結果は `{1}`。

真の漸化式の次数が高々 $L$ と分かっている場合、通常は少なくとも $2L$ 項を与える。有限の入力だけから、それ以降も同じ規則が続くことを保証するものではない。

入力長 $N$ に対して時間 $O(N^2)$、領域 $O(N)$。

#### 実装・検証

- [実装](../../fps/berlekamp-massey.hpp)
- [検証: yosupo-linear-recurrence.test.cpp](../../verify/verify-yosupo-fps/yosupo-linear-recurrence.test.cpp)
