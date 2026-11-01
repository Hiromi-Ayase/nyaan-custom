## 二項係数の部分和の多点評価

`multipoint_binomial_sum<mint>(qs)` は各組 `(n,m)` に対する $\sum_{k=0}^{m}\binom nk$ を、入力と同じ順序で返す。

各問い合わせは `0 <= m <= n`。係数には奇素数の modint を使い、最大の `n` と階乗表に必要な余裕が法未満となるようにする。`2` の逆元を使うので法 `2` は対象外。

Mo のアルゴリズムで `(n,m)` を移動し、部分和の漸化式で 1 ステップを定数時間で更新する。最大の `n` を $N$、問い合わせ数を $Q$ とすると、表の準備に $O(N)$、クエリの処理は Mo の移動回数に比例し、おおむね $O(N\sqrt Q+Q)$。領域は $O(N+Q)$。

#### 実装・検証

- [実装](../../modulo/multipoint-binomial-sum.hpp)
- [Verify: factorial-and-binomial-prefix.cpp](../../tests/unit/modulo/factorial-and-binomial-prefix.cpp)
