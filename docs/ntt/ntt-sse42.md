## SSE による数論変換

`NTT<mint>` は対応した 32 bit Montgomery modint の内部値を SIMD で処理する実装。

- `ntt(a, n)` はポインタ上の長さ `n` の順変換。
- `intt(a, n, normalize = true)` は逆変換。`false` なら長さの逆元を掛けない。
- `multiply(a,b)` は非空のベクトル同士の通常の畳み込み。

変換長は 2 冪で `n <= 1<<23`、かつ法 `p` の `p-1` を割り切る必要がある。内部表の初期化のため `v2(p-1) >= 3` の法を使う。SIMD ポインタ版では実装が要求するアラインメントを満たす領域を用意し、対象 CPU の命令対応も確認する。

時間 $O(n\log n)$。固定のグローバルバッファを共有するため並行利用はできない。通常版・AVX2 版と同名の型を定義するため併用しない。

#### 実装・検証

- [実装](../../ntt/ntt-sse42.hpp)
- [検証: yosupo-convolution-ntt-sse42.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-ntt-sse42.test.cpp)
