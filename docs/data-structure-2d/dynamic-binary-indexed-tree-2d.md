## 動的二次元 Fenwick Tree

`DynamicFenwickTree2D<T>(n,m)` は第1軸に配列、第2軸に疎な Fenwick Tree を持つ。

`add(i,j,x)` は一点加算、`sum(n,m)` は `[0,n) × [0,m)`、`sum(nl,ml,nr,mr)` は半開矩形の和。各添字は構築した範囲内とし、更新には負の添字を渡さない。

各操作は期待 $O(\log n\log m)$ のハッシュ表処理。第1軸には $O(n)$ 個の BIT を確保するため、両軸とも完全に疎な実装ではない。コピーは内部ポインタを共有し、デストラクタによる解放は行わない。

#### 実装・検証

- [実装](../../data-structure-2d/dynamic-binary-indexed-tree-2d.hpp)
- [検証: yosupo-point-add-rectangle-sum-bit2d.test.cpp](../../verify/verify-yosupo-ds/yosupo-point-add-rectangle-sum-bit2d.test.cpp)
