## Montgomery modint の高速行列積

`FastMatProd::strassen(s, t)` は行をベクトルで表した行列の積を返す。`block_dec(s, t)` はブロック分割による通常の行列積。

現実装の係数型は `FastMatProd::mint = LazyMontgomeryModInt<998244353>` に固定される。テンプレート引数は行のコンテナ型であり、任意の係数型を選ぶためのものではない。入力は非空の長方形行列で、`s` の列数と `t` の行数を一致させる。

大きい行列は Strassen 法で分割し、小さい行列や細長い行列では SIMD による積へ切り替える。正方行列の漸近時間は $O(n^{\log_2 7})$。

AVX2 対応 CPU が必要。`BUFFER_SIZE`（既定 `1<<23`）要素の作業配列を 3 本持ち、入力・出力と再帰用の領域が収まる必要がある。共有バッファを使うため並行呼び出しには対応しない。

#### 実装・検証

- [実装](../../modulo/strassen.hpp)
- [Verify: strassen.cpp](../../tests/unit/modulo/strassen.cpp)
