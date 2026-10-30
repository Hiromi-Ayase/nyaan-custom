## AND 畳み込み

`and_convolution(a,b)` は `c[k] = Σ a[i]*b[j]`（`i AND j == k`）を返す。入力は同じ正の 2 冪長とし、値渡しなので元配列は変更しない。

上位集合ゼータ変換で積を成分ごとの乗算へ変換する。値型には加減算・乗算が必要。

長さを $N=2^n$ とすると、時間 $O(n2^n)$、領域 $O(2^n)$。

#### 実装・検証

- [実装](../../set-function/and-convolution.hpp)
- [検証: set-function.test.cpp](../../verify/verify-unit-test/set-function.test.cpp)
