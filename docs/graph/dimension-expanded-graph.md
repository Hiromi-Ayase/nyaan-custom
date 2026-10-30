## 次元拡張グラフ

多次元格子の座標を一次元の頂点番号に変換し、探索・Union Find を座標型で記述する補助クラス。

- `DimensionExpandedGraph<DIM, Data_t> g(s0, s1, ...)`: 各軸の長さを指定する。`Data_t` は符号付き型。
- `A`: 座標型。`cast(...)`, `id(...)`, `ok(...)` で生成・番号変換・範囲判定する。
- `a.near()`: 格子内の軸方向の隣接座標を返す。障害物の判定は呼び出し側で行う。
- `scan()`, `operator()(...)`, `find(char)`: 格子文字列の入力・参照・文字探索。見つからない座標は `ok` で判定する。
- `add(n)`, `ad(i)`: 追加頂点を登録・参照する。追加頂点の座標表現には `DIM >= 2` が必要。
- `dijkstra(f, s)`: `f(現在座標, add)` 内で `add(遷移先, 非負の辺重み)` を呼び、距離配列を得る。到達不能は `-1`。
- `uf(f)`: 各格子点に `f(座標, unite)` を呼んで初期化する。その後 `same`, `unite`, `size` が使える。

#### 現在の実装の制約

サイズ・座標変換情報は同じテンプレート引数のインスタンス間で共有される。`A::operator+` と `operator-` は左辺自身も変更する。

`bfs` はスタックで探索するため一般の最短距離を保証しない。`bfs01` も一度発見した頂点を緩和し直さないため、一般の 0-1 最短路には使えない。`dijkstra` の配列は格子点数 `N` 個なので追加頂点には対応しない。最短路が必要なら、通常のグラフへ変換するか、これらの制約を避けて利用する。

座標変換は $O(DIM)$、格子保持は $O(N)$。Dijkstra は座標処理・コールバックのコストに加え $O((N+E)\log(N+E))$ を要する。

#### 実装・検証

- [実装](../../graph/dimension-expanded-graph.hpp)
- [検証: aoj-1130-DG-bfs.test.cpp](../../verify/verify-aoj-other/aoj-1130-DG-bfs.test.cpp)
- [検証: aoj-2945-DG-01bfs.test.cpp](../../verify/verify-aoj-other/aoj-2945-DG-01bfs.test.cpp)
- [検証: yuki-0697.test.cpp](../../verify/verify-yuki/yuki-0697.test.cpp)
