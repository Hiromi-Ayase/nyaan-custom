## Monotone Minima

各行の最小値を与える列番号が行番号について非減少となる `N × M` 行列に対し、行ごとの argmin を求める。

`monotone_minima(N,M,f)` の `f(i,j,k)` は `j < k` の候補について `A[i][j] <= A[i][k]` を判定する。`monotone_minima<T>(N,M,A)` には値を返す `A(i,j)` を渡す。引数の型は `std::function`。

`N > 0` なら `M > 0` が必要。同値の扱いを含めて argmin の単調性を満たすこと。行数・列数を含む保守的な時間上界は $O(N+M\log(N+1))$、結果領域は $O(N)$。

#### 実装・検証

- [実装](../../dp/monotone-minima.hpp)
- [関連検証（間接使用）: yosupo-concave-min-plus-convolution-1.test.cpp](../../verify/verify-yosupo-math/yosupo-concave-min-plus-convolution-1.test.cpp)
- [関連検証（間接使用）: yosupo-concave-min-plus-convolution-2.test.cpp](../../verify/verify-yosupo-math/yosupo-concave-min-plus-convolution-2.test.cpp)
- [関連検証（間接使用）: yuki-0952.test.cpp](../../verify/verify-yuki/yuki-0952.test.cpp)
