## 静的な点集合の矩形和

`RectangleSum<T,U,F>(xs,ys,ws,f)` は同じ長さの座標列・重み列から構築する。`T` は座標、`U` は重み、`f` は加算として働く結合演算。

`rect_sum(x1,y1,x2,y2)` は半開矩形の重み和。三引数の `rect_sum(x1,x2,y)` は `x1 <= x < x2` かつ `点の y 座標 < y` の和であり、y の下限を 0 に制限しない。

永続 Segment Tree の版を座標で選ぶ。更新はできず、`U` には零・加減算が必要。前処理・領域 $O(n\log n)$、問い合わせ $O(\log n)$。

#### 実装・検証

- [実装](../../data-structure-2d/rectangle-sum.hpp)
- [Verify: rectangles.cpp](../../tests/unit/data-structure-2d/rectangles.cpp)
