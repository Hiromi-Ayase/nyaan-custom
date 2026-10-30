## 転倒数と隣接交換距離

`inversion_counting(v)` は `i < j` かつ `v[i] > v[j]` となる組数を `long long` で返す。同じ値は転倒に数えない。

`swap_distance(v,w)` は隣接要素の交換だけで `v` を `w` にする最小回数。同じ値の出現を順に対応させる。長さや多重集合が異なる場合は `-1`。

座標圧縮と BIT を用い、いずれも時間 $O(n\log n)$、領域 $O(n)$。

#### 実装・検証

- [実装](../../dp/inversion-counting.hpp)
- [検証: yuki-1115.test.cpp](../../verify/verify-yuki/yuki-1115.test.cpp)
