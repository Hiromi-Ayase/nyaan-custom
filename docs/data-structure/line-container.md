## 直線の追加と最小値・最大値

`MinLineContainer<T>` / `MaxLineContainer<T>` に `add(k,m)` で直線 `y=k*x+m` を追加し、`query(x)` で最小値・最大値を得る。傾きや問い合わせ順に制限はない。空集合には問い合わせない。

`T` は符号付き整数または `long double`。整数版では交点を負の無限大方向に丸める。係数差・積・符号反転が型に収まることが必要。浮動小数点版には丸め誤差がある。

追加は償却 $O(\log n)$、取得は $O(\log n)$、領域は $O(n)$。継承元の `multiset` を直接変更すると包絡線の不変条件が壊れる。

#### 実装・検証

- [実装](../../data-structure/line-container.hpp)
- [Verify: line-container.cpp](../../tests/unit/data-structure/line-container.cpp)
