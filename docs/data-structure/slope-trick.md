## Slope Trick（ヒープ）

`SlopeTrick` は初期関数 0 から凸区分線形関数を管理する。座標・傾き・値は `long long`。

`add_xma(a,c)` は `c*max(x-a,0)`、`add_amx(a,c)` は `c*max(a-x,0)`、`add_abs_xma(a,c)` は `c*abs(x-a)` を加える。`c` は非負、既定値 1。

`get_min()` は `(最小点の一つ, 最小値)`。`shift_x(a)` は `f(x-a)`、`shift_y(a)` は定数加算。`chmin_right()` は接頭側の最小値、`chmin_left()` は接尾側の最小値へ置き換える。左右の折れ点だけを動かす `shift_L/R` は左右の順序を保つように使う。`merge(r)` は関数を加算する破壊的操作。

最小値・平行移動は $O(1)$。追加は移動させる折れ点数 $k$ に対し $O((k+1)\log n)$。`eval(x)` はヒープをコピーして走査するため最悪 $O(n\log n)$。重み付き版も `SlopeTrick` を定義するので同時に include しない。

#### 実装・検証

- [実装](../../data-structure/slope-trick.hpp)
- [検証: yuki-1467.test.cpp](../../verify/verify-yuki/yuki-1467.test.cpp)
