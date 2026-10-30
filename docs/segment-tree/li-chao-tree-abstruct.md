## Li Chao Tree（関数型・区間取得対応）

`LiChaoTree<Line,MINIMIZE=true,RANGE_GET=false>` は `Line::operator()(long long)` で評価できる関数を管理する。任意の二関数の優劣が座標順に高々一度しか切り替わらないことが必要。

- `(xs,I)` / `(n,I)`: 評価座標列、または `[0,n)` の整数座標から構築する。`I` はすべての評価点で中立となるダミー関数。非空の座標集合が必要。
- `add_line(f)` / `add_segment(xl,xr,f)`: 全体または**半開区間** `[xl,xr)` に関数を追加する。
- `get_val(x)`: 登録座標 `x` での `(最適値, それを与える関数)`。
- `get(xl,xr)`: 範囲内の `(座標, 最適値)`。`RANGE_GET=true` が必要で、各関数の区間内最適値が端点に現れる単調性も必要。

`MINIMIZE=false` なら最大化する。構築は $O(n\log n)$、全体追加・点取得・区間取得は $O(\log n)$、線分追加は $O(\log^2 n)$。`li-chao-tree.hpp` と同名のクラスを定義するため併用しない。

#### 実装・検証

- [実装](../../segment-tree/li-chao-tree-abstruct.hpp)
- [検証: li-chao-tree-abstruct.test.cpp](../../verify/verify-unit-test/li-chao-tree-abstruct.test.cpp)
- [検証: yosupo-concave-min-plus-convolution-3.test.cpp](../../verify/verify-yosupo-math/yosupo-concave-min-plus-convolution-3.test.cpp)
- [検証: yosupo-concave-min-plus-convolution-4.test.cpp](../../verify/verify-yosupo-math/yosupo-concave-min-plus-convolution-4.test.cpp)
