## 両端操作できる Sliding Window Aggregation

`SlideWindowAggregationDeque<T,F>(f,I)` は結合的演算 `f` と単位元 `I` を持つ deque。可換性は不要。

`push_front/back(x)`, `pop_front/back()`, `front()`, `back()` が使え、`query()` は先頭から末尾の順に畳み込んだ値を返す。空なら `I`。空の参照・削除は禁止。

二つの集約スタックを再配分する。両端操作は償却 $O(1)$、集約取得は $O(1)$、領域は要素数に比例する。

#### 実装・検証

- [実装](../../data-structure/slide-window-aggregation-deque.hpp)
- [Verify: sliding-aggregation.cpp](../../tests/unit/data-structure/sliding-aggregation.cpp)
