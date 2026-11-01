## 閉路の検出

`CycleDetection(g, directed = true)` は閉路を一つ探し、その辺を `(from, to)` の列で返す。辺は閉路をたどる順に並ぶ。閉路がなければ空の配列を返す。

- 有向グラフでは `directed = true`、無向グラフでは `false` を指定する。
- 自己ループは `{(v, v)}` として返す。
- 無向グラフでは親への辺をすべて読み飛ばすため、平行な二辺からなる閉路の検出には使えない。

時間は $O(V+E)$、追加領域は $O(V)$。再帰 DFS を使用する。

#### 実装・検証

- [実装](../../graph/cycle-detection.hpp)
- [Verify: directed.cpp](../../tests/unit/graph/directed.cpp)
