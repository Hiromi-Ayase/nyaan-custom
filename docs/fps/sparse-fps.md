## 疎な多項式の FPS 演算

入力の非零項だけを列挙し、係数の漸化式から次数 `deg` 未満の結果を求める。`deg` の省略時は主な入力の長さ。

- `sparse_div(f,g,deg)` は `f/g`。`g` が疎で定数項が可逆であること。
- `sparse_inv(f,deg)` は逆数。`f` の定数項が可逆であること。
- `sparse_log(f,deg)` は対数。`f[0] = 1`。
- `sparse_exp(f,deg)` は指数関数。空または定数項 `0`。
- `sparse_pow(f,k,deg)` は非負整数乗。低次の零も扱う。一般の入力では `deg >= 1` として呼ぶ。

対数・指数・累乗は次数に対応する整数の逆元を使うため、素数の法で計算次数を法未満にする。静的な逆元表を使うので、同じ modint 型の法を途中で切り替えない。

疎な側の非零項数を $K$、出力長を $N$ とすると時間 $O(NK)$ に入力走査の費用が加わり、領域 $O(N+K)$。高速な NTT は不要。

#### 実装・検証

- [実装](../../fps/sparse-fps.hpp)
- [検証: fps-sparse.test.cpp](../../verify/verify-unit-test/fps-sparse.test.cpp)
- [検証: yosupo-sparse-exp.test.cpp](../../verify/verify-yosupo-fps/yosupo-sparse-exp.test.cpp)
- [検証: yosupo-sparse-inv.test.cpp](../../verify/verify-yosupo-fps/yosupo-sparse-inv.test.cpp)
