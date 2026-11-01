## 矩形加算・矩形和（オフライン）

`RectangleAddRectangleSum<I,T>` は座標型 `I`、集計型 `T` で矩形の重なりを集計する。

`add_rectangle(xl,xr,yl,yr,val)` で半開矩形への加算を登録し、`add_query(xl,xr,yl,yr)` で問い合わせを登録する。引数順は **x の両端、y の両端**。`solve()` は問い合わせの登録順に答えを返す。

すべての加算がすべての問い合わせへ適用され、時系列の更新・取得ではない。答えは交差矩形の面積に値を掛けた総和（整数格子ではセルの和）。座標差と積を `T` で扱えること。

加算数と問い合わせ数の合計を $n$ とすると、時間 $O(n\log n)$、領域 $O(n)$。

#### 実装・検証

- [実装](../../data-structure-2d/rectangle-add-rectangle-sum.hpp)
- [Verify: rectangles.cpp](../../tests/unit/data-structure-2d/rectangles.cpp)
