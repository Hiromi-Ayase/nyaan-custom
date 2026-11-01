## HashMap / HashSet の基底実装

`HashMapImpl::HashMapBase<Key,Data>` は開番地法のバケット・削除フラグ・再配置・iterator を実装する。利用者は通常 `hashmap.hpp` の `HashMap` または `hashset.hpp` の `HashSet` を選ぶ。

`find`, `contain`, `insert`, `erase`, `begin/end` などを共通化する。整数・整数 pair・整数列のハッシュに対応する。iterator の走査順はバケット順で、キー順ではない。

再配置で iterator・参照が無効になる。期待償却の検索・更新は定数時間（キーのハッシュ計算を除く）、走査は容量に比例。`std::iterator` を使用するため C++17 向け。

#### 実装・検証

- [実装](../../hashmap/hashmap-base.hpp)
- [Verify: maps-and-sets.cpp](../../tests/unit/hashmap/maps-and-sets.cpp)
