## 削除なしのハッシュマップ

`UnerasableHashMap<Key,Val,fixed_size=false,get_hash>(default_value,default_size)` は線形探索法のハッシュ表。

`operator[](key)` は未登録なら初期値で挿入し、`get(key)` は挿入せず初期値を返す。`count/contain`, `size`, `enumerate(f)`、`clear/reset` を提供する。個別削除はない。

可変サイズ版は容量 4 から始まり、`default_size` は無視される。固定版は容量を十分大きく取り、空きバケットを必ず残す。再配置は参照を無効にする。

ハッシュが適切なら検索・追加は期待償却 $O(1)$。列挙・初期化は容量に比例する。

#### 実装・検証

- [実装](../../hashmap/hashmap-unerasable.hpp)
- [検証: aoj-1377.test.cpp](../../verify/verify-aoj-other/aoj-1377.test.cpp)
- [検証: internal-type-traits.test.cpp](../../verify/verify-unit-test/internal-type-traits.test.cpp)
- [検証: yosupo-associative-array-unerasable-hashmap.test.cpp](../../verify/verify-yosupo-ds/yosupo-associative-array-unerasable-hashmap.test.cpp)
