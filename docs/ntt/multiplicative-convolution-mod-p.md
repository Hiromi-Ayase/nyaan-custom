## 添字の積に関する畳み込み

`multiplicative_convolution_mod_p(a,b,p)` は $c[k]=\sum_{ij\equiv k\pmod p}a[i]b[j]$ を返す。

`p` は素数、両配列の長さはちょうど `p`。これは添字を計算する法で、係数の modint の法と一致する必要はない。係数列には通常の多項式積 `operator*` が必要。

非零の添字を原始根の指数へ変換し、長さ `p-1` の巡回畳み込みとして処理する。添字 `0` の寄与は別に加える。結果は長さ `p` で、入力を変更しない。

高速な多項式積を使う場合、原始根探索を除く時間は $O(p\log p)$、領域 $O(p)$。

#### 実装・検証

- [実装](../../ntt/multiplicative-convolution-mod-p.hpp)
- [検証: yosupo-convolution-on-z-pz.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-on-z-pz.test.cpp)
