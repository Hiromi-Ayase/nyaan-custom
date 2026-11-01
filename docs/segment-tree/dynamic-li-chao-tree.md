## 動的 Li Chao Tree

整数座標の閉区間 `[xmin,xmax]` で直線の最小値を管理する設計の実装。

- `DynamicLiChaoTree<T,INF>(xmin,xmax)`: 座標範囲を指定する。
- `update(a,b)`: 直線 `a*x+b` の追加。
- `update_line_segment(a,b,left,right)`: 閉区間 `[left,right]` の線分追加。
- `query(x)`: 範囲内の座標での最小値。候補がなければ `INF`。

`data-structure/hash-map-variable-length.hpp` を内部で利用する。`T` 型で座標・節点番号・`a*x+b` がオーバーフローしない範囲を指定する。

想定する木の高さは $O(\log(xmax-xmin+1))$。直線追加・点取得はこの高さに比例、線分追加は高さの二乗に比例するハッシュ表アクセスを行う。

#### 実装・検証

- [実装](../../segment-tree/dynamic-li-chao-tree.hpp)
- [Verify: li-chao.cpp](../../tests/unit/segment-tree/li-chao.cpp)
