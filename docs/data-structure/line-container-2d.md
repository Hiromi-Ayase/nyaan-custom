## 二次元点集合の線形目的関数

`LineContainer2D` に `add(x,y)` で点を追加し、点集合上の `a*x+b*y` の最大・最小を問い合わせる。

`max_ld(a,b)` / `min_ld(a,b)` は `long double`、`max_ll(a,b)` / `min_ll(a,b)` は整数向けの返却を行う。内部の包絡線は浮動小数点なので、大きな整数に対する厳密計算の代用にはしない。空集合への問い合わせは禁止。

追加は償却 $O(\log n)$、問い合わせは $O(\log n)$、領域は $O(n)$。

#### 実装・検証

- [実装](../../data-structure/line-container-2d.hpp)
- [検証: yuki-2012.test.cpp](../../verify/verify-yuki/yuki-2012.test.cpp)
