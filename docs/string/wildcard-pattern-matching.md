## ワイルドカード付きパターン照合

`wildcard_pattern_matching(a,b,wildcard=0)` は `a` 中の各開始位置で `b` が一致するかを 0/1 の配列で返す。ワイルドカードは両方の列で任意の一要素に一致する。

通常の返却長は `|a|-|b|+1`。`b` が空なら長さ `|a|+1` の全 1、`|b|>|a|` なら空。要素は整数や文字など modint に変換可能な型とする。

三つの法で差の二乗和を畳み込む。すべての法で 0 でも、値域次第では真の一致とは限らない。NTT の変換長上限内で使用する。時間 $O((n+m)\log(n+m))$、領域 $O(n+m)$。

#### 実装・検証

- [実装](../../string/wildcard-pattern-matching.hpp)
- [検証: yosupo-wildcard-pattern-matching.test.cpp](../../verify/verify-yosupo-string/yosupo-wildcard-pattern-matching.test.cpp)
- [検証: yuki-2231.test.cpp](../../verify/verify-yuki/yuki-2231.test.cpp)
