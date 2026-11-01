## Li Chao Tree（座標圧縮）

事前に指定した座標で、追加した一次関数の最小値を取得する。

- `LiChaoTree<T,INF>(xs)`: 非空の評価座標列から構築する。重複は除去される。
- `update(a,b)`: 直線 `y = a*x+b` を追加する。
- `update_segment(a,b,low,high)`: **閉区間** `[low,high]` に有効な線分を追加する。境界は登録座標の範囲内に収める。
- `query(x)` / `query_idx(k)`: 登録済み座標またはソート後の座標番号で最小値を得る。直線がなければ `INF`。

未登録の `x` は右隣の登録座標に丸められるため、必ず事前登録した点で問い合わせる。座標も `T` 型で評価する。`a*x+b` と座標のパディングがオーバーフローしないこと。

構築は $O(n\log n)$、直線追加・点取得は $O(\log n)$、線分追加は $O(\log^2 n)$、領域は $O(n)$。抽象版と同名の `LiChaoTree` を定義するため、同時に include しない。

#### 実装・検証

- [実装](../../segment-tree/li-chao-tree.hpp)
- [Verify: li-chao.cpp](../../tests/unit/segment-tree/li-chao.cpp)
