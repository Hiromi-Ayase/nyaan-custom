## 各辺数に対する Monge 最短路の列挙

`enumerate_monge_d_edge_shortest_path(N,f,unreached)` は、Monge な完全 DAG の 0 から N への D 辺最短路を `D=1,...,N` について返す。

戻り値は長さ `N+1` で、`ans[D]` がコスト。`ans[0]` は引数 `unreached`（既定値 `(1LL<<62)-1`）のまま。辺は小さい番号から大きい番号へ張り、`f(i,j)` は `long long` を返す。

内部の DP は `__int128_t`。返却コストは `long long` に収まること。時間 $O(N^2\log N)$、領域 $O(N)$。

#### 実装・検証

- [実装](../../dp/monge-d-edge-shortest-path-enumerate.hpp)
- [Verify: monge.cpp](../../tests/unit/dp/monge.cpp)
