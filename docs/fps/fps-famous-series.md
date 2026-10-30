## 代表的な数列の母関数

係数は低次順。`Binomial<mint>& C` を受け取る関数には、必要な階乗・逆元が使える法と FPS の積のバックエンドを用意する。

- `Stirling1st(N,C)` は符号なし第一種 Stirling 数の第 `N` 行。$x(x+1)\cdots(x+N-1)$ の係数を返す。
- `Stirling2nd(N,C)` は第二種 Stirling 数 `S(N,k)` を `k=0..N` で返す。
- `Stirling1stRow(K,upper,C)` / `Stirling2ndRow(K,upper,C)` は第 2 添字を `K` に固定して、第 1 添字 `0..upper` を列挙する。`upper < K` なら空配列。
- `BernoulliEGF(N,C)` は $x/(e^x-1)$ の次数 `0..N`、すなわち `B[i]/i!`。この規約では `B[1] = -1/2`。
- `Partition(N,C)` は分割数 `p(0)..p(N)`。
- `Montmort<mint>(N)` は通常の `D(0)` 始まりではなく、長さ `N` に `D(1)..D(N)` を入れる。`N <= 1` では `{0}` を返す。

添字は非負とする。Stirling 数や Bernoulli 数では必要な階乗の添字を法未満にする。多項式演算を使う関数は準線形時間、Montmort 数は線形時間。

#### 実装・検証

- [実装](../../fps/fps-famous-series.hpp)
- [検証: yosupo-stirling-1st-row.test.cpp](../../verify/verify-yosupo-fps/yosupo-stirling-1st-row.test.cpp)
- [検証: yosupo-stirling-1st.test.cpp](../../verify/verify-yosupo-fps/yosupo-stirling-1st.test.cpp)
- [検証: yosupo-stirling-2nd-row.test.cpp](../../verify/verify-yosupo-fps/yosupo-stirling-2nd-row.test.cpp)
