## 整数の基数ソート

整数の各バイトを順に数え上げ、昇順に整列する。

- `radix_sort(v)` / `radix_sort(N, p)` は配列を直接並べ替える。キーは 32 bit または 64 bit の整数型。
- `radix_sort_compare_first(v)` / `radix_sort_compare_first(N, p)` は `pair<T, U>` の `first` をキーに安定ソートする。同じキーの要素は元の順序を保ち、`second` は比較しない。
- 符号付き整数では負数が先に来るように補正する。

要素数が `64` 以下なら比較ソートへ切り替える。キーのバイト数を $w$ として時間 $O(w(N+256))$、追加領域 $O(N)$。作業バッファを静的に共有するため、同じ特殊化への並行呼び出しには対応しない。

#### 実装・検証

- [実装](../../math-fast/radix-sort.hpp)
- [検証: radix-sort.test.cpp](../../verify/verify-unit-test/radix-sort.test.cpp)
