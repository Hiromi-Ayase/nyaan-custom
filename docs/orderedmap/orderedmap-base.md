## 順序付き map の RBST 基底

`OrderedMapBase<Node,multi>` はキー順に節点を配置する基底クラス。`Node` は `key,l,r,cnt` とキーを受けるコンストラクタを持つ。

派生クラスは protected の `insert_key(k)` を使って挿入 API を定義する。`multi=false` は重複キーを既存節点へ統合し、`true` は別節点にする。`find`, `count`, `erase`, `kth_element`, `lower_bound`, `upper_bound` を提供する。

`erase(key)` は重複があっても一要素だけを削除する。境界検索は順位を返す。操作は期待 $O(\log n)$。通常は `OrderedMap` を直接使う。

#### 実装・検証

- [実装](../../orderedmap/orderedmap-base.hpp)
- [関連検証（間接使用）: orderedmap.test.cpp](../../verify/verify-unit-test/orderedmap.test.cpp)
- [関連検証（間接使用）: yosupo-orderedmap.test.cpp](../../verify/verify-yosupo-ds/yosupo-orderedmap.test.cpp)
