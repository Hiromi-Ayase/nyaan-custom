## van Emde Boas 型の整数集合

`van_Emde_Boas_tree` は `[0,2^24)` を扱う固定サイズの整数集合。

`insert`, `erase`, `contain`, `empty`, `min`, `max` に加え、`find_next(k)` は `k` 以上、`find_prev(k)` は `k` 未満の要素を探す。該当要素がない場合の返り値は `-1`。

上位・下位ビットへ再帰分割し、末端を 64 ビット整数で保持する。集合が空でも全領域を確保するため、メモリは台集合の大きさに比例する。この実装の挿入・削除は複数の子へ再帰するので、一般的な vEB 木の計算量をそのまま当てはめない。

#### 実装・検証

- [実装](../../data-structure/van-emde-boas-tree.hpp)
- [検証: yosupo-predecessor-problem-vEB-tree.test.cpp](../../verify/verify-yosupo-ds/yosupo-predecessor-problem-vEB-tree.test.cpp)
