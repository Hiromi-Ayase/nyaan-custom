## 順序統計付き連想配列

`OrderedMap<Key,Val>` は RBST による順序付き map。`map[key]` で値を参照し、未登録キーは `Val()` で作る。

`find(key)` は節点ポインタ（未発見は null）、`lower_bound/upper_bound(key)` は iterator ではなくキー未満・以下の要素数。`kth_element(k)` は 0 始まりで k 番目の節点。`erase`, `count`, `size` も利用できる。

各検索・更新は期待 $O(\log n)$、領域 $O(n)$。コピーは節点を共有し、std::map と同じ所有権・iterator API ではない。

#### 実装・検証

- [実装](../../orderedmap/orderedmap.hpp)
- [Verify: ordered-map.cpp](../../tests/unit/orderedmap/ordered-map.cpp)
