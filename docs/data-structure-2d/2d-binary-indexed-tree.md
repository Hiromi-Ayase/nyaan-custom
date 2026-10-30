## 二次元 Binary Indexed Tree

`BinaryIndexedTree2D<T>(H,W)` は 0 始まりの二次元配列を保持する。`add(x,y,w)` で一点加算、`sum(x,y)` で `[0,x] × [0,y]`、`sum(x1,y1,x2,y2)` で閉矩形の和を取得する。

`imos(x1,y1,x2,y2,w)` は閉矩形への差分加算。この用法では `sum(x,y)` が一点値となり、通常の一点加算・矩形和とは混在させない。四引数の `sum` は端点が逆なら 0 を返す。

時間は各操作 $O(\log H\log W)$、構築・領域は $O(HW)$。内部には境界用に一行・一列を余分に確保する。

#### 実装・検証

- [実装](../../data-structure-2d/2d-binary-indexed-tree.hpp)
- [検証: aoj-dsl-5-b-bit2d.test.cpp](../../verify/verify-aoj-dsl/aoj-dsl-5-b-bit2d.test.cpp)
