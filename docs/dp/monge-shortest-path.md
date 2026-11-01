## Monge な DAG の最短路

`monge_shortest_path<T>(N,f)` は頂点 `0,...,N`、辺 `i -> j`（`i < j`）のコスト `f(i,j)` を用い、0 から全頂点への距離を返す。

コストは Monge 性、すなわち適用可能な `i < j < k < l` で `f(i,k)+f(j,l) <= f(i,l)+f(j,k)` を満たすことが必要。戻り値の長さは `N+1`、先頭は 0。`T` は符号付き整数を想定し、内部の大きな番兵値との加算も収まるようにする。

分割統治による時間 $O(N\log N)$、領域 $O(N)$（コスト評価を $O(1)$ とする）。

#### 実装・検証

- [実装](../../dp/monge-shortest-path.hpp)
- [Verify: monge.cpp](../../tests/unit/dp/monge.cpp)
