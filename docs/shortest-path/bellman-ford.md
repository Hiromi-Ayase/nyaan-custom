## Bellman–Ford 法

負の重みを許す有向グラフの単一始点最短路を求める。

`bellman_ford(N, es, start = 0, goal = -1)` に頂点数、`vector<tuple<int, int, T>>` 型の辺列（要素は `(始点, 終点, 重み)`）、始点を渡す。到達不能の距離は `numeric_limits<T>::max() / 2`。

- `goal == -1`: 始点から到達可能な負閉路があれば空の配列を返す。
- `goal` 指定時: 始点から到達でき、さらに終点に影響する負閉路がある場合だけ空を返す。
- `goal` に影響しない負閉路がある場合、返却配列のうちその負閉路の影響を受ける頂点の値は最短距離ではない。

時間は $O(VE)$、領域は $O(V)$。負辺と繰り返し緩和の中間値を表せる符号付きの `T` を使う。

#### 実装・検証

- [実装](../../shortest-path/bellman-ford.hpp)
- [Verify: negative-edges.cpp](../../tests/unit/shortest-path/negative-edges.cpp)
