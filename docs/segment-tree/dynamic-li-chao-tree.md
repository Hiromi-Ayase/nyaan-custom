## 動的 Li Chao Tree

整数座標の閉区間 `[xmin,xmax]` で直線の最小値を管理する設計の実装。

- `DynamicLiChaoTree<T,INF>(xmin,xmax)`: 座標範囲を指定する。
- `update(a,b)`: 直線 `a*x+b` の追加。
- `update_line_segment(a,b,left,right)`: 閉区間 `[left,right]` の線分追加。
- `query(x)`: 範囲内の座標での最小値。候補がなければ `INF`。

現在は include 先の `data-structure/hash-map-variable-length.hpp` がリポジトリに存在しないため、このヘッダだけでは利用できない。依存を整備してから使うか、座標を事前登録できる場合は `li-chao-tree.hpp` を使う。

想定する木の高さは $O(\log(xmax-xmin+1))$。直線追加・点取得はこの高さに比例、線分追加は高さの二乗に比例するハッシュ表アクセスを行う。

#### 実装・検証

- [実装](../../segment-tree/dynamic-li-chao-tree.hpp)
- [検証: yosupo-dynamic-li-chao-tree.test.cpp](../../verify/verify-yosupo-ds/yosupo-dynamic-li-chao-tree.test.cpp)
