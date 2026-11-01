## 配列上の二分探索

昇順に整列した配列の挿入位置を、分岐を抑えた二分探索で求める。

- `fast_lb(v, x)` は `x` 以上の最初の要素の添字、`fast_ub(v, x)` は `x` より大きい最初の要素の添字を返す。見つからなければ `v.size()`、空配列なら `0`。
- `fast_bs(v, x, comp)` は `comp(x, v[i])` が初めて真になる位置を返す。この述語が配列上で偽から真へ一度だけ変化する必要がある。

計算量は $O(\log n)$、追加領域は $O(1)$。比較対象にはランダムアクセスが必要。

#### 実装・検証

- [実装](../../math-fast/binary-search.hpp)
- [Verify: basic.cpp](../../tests/unit/math-fast/basic.cpp)
