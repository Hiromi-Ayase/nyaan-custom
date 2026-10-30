## 行列積を用いた FPS 合成

`Composition(P, Q, deg = -1)` は $Q(P(x))\bmod x^{deg}$ を計算する旧実装。省略時の長さは **`min(P.size(), Q.size())`** で、新しい `composition` と異なる。

このヘッダは `mint = LazyMontgomeryModInt<998244353>` と `fps` を定義し、法を固定する。AVX2 対応 CPU と FPS の積のバックエンドが必要。

入力を約 $\sqrt N$ 個のブロックへ分け、冪の前計算と Strassen 行列積を使う。内部では外側の係数を最大 $K^2$ 個（$K=\lceil\sqrt N\rceil$）まで扱う。`P[0] = 0` なら低次 $N$ 項にはそれ以降の係数は影響しない。非零の定数項を使う場合は外側の全係数が収まることが必要。

時間は $O(N^2)$ 以下、冪の表に $O(N\sqrt N)$ 領域を使う。行列積の固定バッファ容量も満たす必要がある。

#### 実装・検証

- [実装](../../fps/fps-composition-fast-old.hpp)
- [検証: yosupo-composition-fast.test.cpp](../../verify/verify-yosupo-fps/yosupo-composition-fast.test.cpp)
