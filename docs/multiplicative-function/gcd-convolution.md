## GCD 畳み込み

`gcd_convolution(a, b)` は $c[k]=\sum_{\gcd(i,j)=k}a[i]b[j]$ を求める。

両配列は同じ長さ `N+1` とし、添字 `1..N` に係数を置く。添字 `0` は使用せず `0` を入れる。入力は値渡しで、元の配列は変更しない。出力も長さ `N+1`。

倍数方向のゼータ変換、成分ごとの積、メビウス変換を用いる。係数型には加減乗算が必要で、整数なら積と和のオーバーフローに注意する。時間は $O(N\log N)$ 以下、領域 $O(N)$。

#### 実装・検証

- [実装](../../multiplicative-function/gcd-convolution.hpp)
- [Verify: basic.cpp](../../tests/unit/multiplicative-function/basic.cpp)
