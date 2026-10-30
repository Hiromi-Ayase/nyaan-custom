## 辺数を指定した Monge 最短路

`monge_d_edge_shortest_path(N,D,upper,f)` は Monge な完全 DAG の頂点 0 から N へ、ちょうど D 辺を使う最小コストを返す。`1 <= D <= N` を想定する。

`f(from,to)` は `long long` の辺コスト。`upper` は最適コストを辺数で一つ変えたときの差の絶対値を覆う罰金探索幅。これが不足すると正しい答えを保証しない。

辺あたり一定の罰金を加えた最短路を整数黄金分割探索する。内部は `__int128_t`、返り値は `long long`。時間 $O(N\log N\log(upper+2))$、領域 $O(N)$。

#### 実装・検証

- [実装](../../dp/monge-d-edge-shortest-path.hpp)
- [検証: yuki-0952.test.cpp](../../verify/verify-yuki/yuki-0952.test.cpp)
