## 二次元累積和

`CumulativeSum2D<T>(H,W)` に `add(i,j,x)` で値を登録し、`build()` を一度呼ぶと `query(i1,j1,i2,j2)` で半開矩形の和を $O(1)$ で取得できる。

差分配列として使う場合は、`imos(i1,j1,i2,j2,x=1)` で半開矩形に加算し、`build()` 後に `imos_get(i,j)` で一点値を読む。二つの用法を区別する。

座標は非負で構築サイズ内とする。`build` は破壊的な累積処理で、追加登録後に繰り返して呼ぶ用途ではない。構築・前処理・領域は $O(HW)$。

#### 実装・検証

- [実装](../../data-structure-2d/2d-cumulative-sum.hpp)
- [検証: aoj-dsl-5-b.test.cpp](../../verify/verify-aoj-dsl/aoj-dsl-5-b.test.cpp)
