## Dirichlet 畳み込みからの累積和列挙

$f*g=h$ と $g(1)=1$ を使って、$S_f(n)=\sum_{i=1}^n f(i)$ を求める。

`enumerate_mf_prefix_sum<T, SG, SH>(N, sg, sh)` に `sg(n) = S_g(n)`、`sh(n) = S_h(n)` を与える。構築後の `get(n)` / `operator()(n)` は、`n = floor(N/i)` となる引数（および `0`）の累積和を返す。大きい任意の引数の問い合わせには使えない。`N >= 1` とし、累積和関数は `0` で `0` を返すものを渡す。

$S_f(n)=S_h(n)-\sum_{l=2}^n g(l)S_f(\lfloor n/l\rfloor)$ の和を商が等しい区間でまとめる。`sg`, `sh` が $O(1)$ なら構築は $O(N^{3/4})$、領域 $O(\sqrt N)$、取得は $O(1)$。

#### 実装・検証

- [実装](../../multiplicative-function/enumerate-sum-of-multiplicative-function.hpp)
- [Verify: prefix.cpp](../../tests/unit/multiplicative-function/prefix.cpp)
