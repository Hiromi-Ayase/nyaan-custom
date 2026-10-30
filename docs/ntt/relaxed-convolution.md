## オンライン畳み込み

`RelaxedConvolution<fps>(N)` は係数を低次から 1 個ずつ受け取り、次数 `0..N` の畳み込みを順に求める。

`get(x,y)` の第 `q` 回の呼び出しで `a[q]=x`, `b[q]=y` を登録し、$c[q]=\sum_{i=0}^q a[i]b[q-i]$ を返す。呼び出しは最大 `N+1` 回。次の係数を決める直前の公開配列 `c[q]` には、`a[0]*b[q]` と `a[q]*b[0]` を除く既知の寄与が蓄積されている。

`fps` は `ntt()` と正規化済みの `intt()` を持つ型とし、使用する最大の変換長が法とバックエンドの制限内に収まるようにする。

2 冪のブロックごとに畳み込みをまとめる。全体で時間 $O(N\log^2 N)$、領域 $O(N)$。1 回ごとの最悪時間が一定ではなく、ブロック境界で変換を行う。

#### 実装・検証

- [実装](../../ntt/relaxed-convolution.hpp)
- [検証: relaxed-convolution.test.cpp](../../verify/verify-unit-test/relaxed-convolution.test.cpp)
- [検証: yosupo-exp-relaxed-convolution.test.cpp](../../verify/verify-yosupo-fps/yosupo-exp-relaxed-convolution.test.cpp)
- [検証: yosupo-inv-relaxed-convolution.test.cpp](../../verify/verify-yosupo-fps/yosupo-inv-relaxed-convolution.test.cpp)
