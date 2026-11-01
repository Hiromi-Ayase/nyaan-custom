## セグメント木状の区間分割

`DivideInterval(n)` は区間の分割に対応する節点番号だけを提供する。`B` は `n` 以上の最小の 2 冪で、葉 `B+i` が要素 `i` に対応する。

`range(l,r)` は半開区間を覆う節点を左から右へ返す。`apply(l,r,f)` は各節点へ `f(id)` を呼ぶ。いずれも $O(\log n)$。

`push(f)` は親から子へ `f(parent,child)`、`update(f)` は葉側から `f(parent,left,right)` を呼ぶ。全節点の処理は $O(n)$。ダミー葉も含めて処理されるので必要なら呼び出し側で除外する。

#### 実装・検証

- [実装](../../data-structure/divide-interval.hpp)
- [Verify: divide-interval.cpp](../../tests/unit/data-structure/divide-interval.cpp)
