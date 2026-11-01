## 重み付き Slope Trick（RBST）

`WeightedSlopeTrick<I>` は凸区分線形関数の折れ点を RBST で管理する。`SlopeTrick` は `WeightedSlopeTrick<__int128_t>` の別名。

`add_xma(a,c)`, `add_amx(a,c)`, `add_abs_xma(a,c)` で、それぞれ `c*max(x-a,0)`, `c*max(a-x,0)`, `c*abs(x-a)` を加える。重みは非負。`get_min()` は `(最小点, 最小値)`、`eval(x)` は点での値。

`shift_x`, `shift_y`, `shift_L/R`, `chmin_left/right`, `merge`, `clear` を提供する。左右別の移動は折れ点の順序を維持する。`merge` は引数との交換を含む破壊的操作として扱う。

追加・評価は期待 $O(\log n)$。平行移動は $O(1)$、折れ点の解放はその個数に比例する。コピーは内部節点を共有するので独立した関数として更新しない。ヒープ版と `SlopeTrick` の名前が衝突する。

#### 実装・検証

- [実装](../../data-structure/slope-trick-weighted.hpp)
- [Verify: slope-trick-weighted.cpp](../../tests/unit/data-structure/slope-trick-weighted.cpp)
