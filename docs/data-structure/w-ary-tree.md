## 64 分木による整数集合

`w_ary_tree<LOG=4>` は `[0,64^LOG)` の整数集合を固定長の階層ビット集合で保持する。

`insert(k)`, `erase(k)`, `contain(k)`、`min()`, `max()`、`find_next(k)`（`k` 以上）、`find_prev(k)`（`k` 未満）を提供する。見つからない場合は `-1`。重複挿入は一要素として扱う。

操作は $O(LOG)$、領域は $O(64^LOG)$ で、要素数によらず全体を確保する。大きなインスタンスをスタックに置かない。現実装の `find_next` は内部の子番号 63 で 64 ビットシフトを評価する箇所があるため、その境界の利用には修正が必要。

#### 実装・検証

- [実装](../../data-structure/w-ary-tree.hpp)
- [Verify: integer-set.cpp](../../tests/unit/data-structure/integer-set.cpp)
