## 状態遷移を関数で与える Dijkstra 法

隣接リストを事前構築せず、任意の状態型 `Index` に対して最短路を探索する。

`dijkstra_abstruct<Index, Cost>(f, start, goal)` を呼ぶ。`goal` には頂点または `bool(Index)` の判定関数を渡せる。`f(v, distance, add)` の中で `add(next, next_distance)` を呼ぶ。第2引数は**辺重みではなく始点からの累積距離**である。

返り値 `DijkstraResult<Index, Cost>` の主なメンバ:

- `reachable`: 条件を満たす終点へ到達したか。
- `goal`, `dist`, `path`: 到達した終点・距離・始点からの頂点列。失敗時はそれぞれデフォルト値・デフォルト値・空列。
- `mp`: 発見した状態から `(距離, 親状態)` への map。終点で打ち切った場合、他の状態には暫定距離が残る。

第3テンプレート引数を `false` にすると全到達状態を探索する。この場合は `reachable == false` となり、結果は `mp` から読む。

`Index` は比較・デフォルト構築可能であること。遷移コストは非負とする。発見状態数を $V$、試す遷移数を $E$ とすると、map とヒープの処理に $O((V+E)\log(V+E))$、領域に $O(V+E)$ を要する。

#### 実装・検証

- [実装](../../shortest-path/dijkstra-abstruct.hpp)
- [Verify: abstract.cpp](../../tests/unit/shortest-path/abstract.cpp)
