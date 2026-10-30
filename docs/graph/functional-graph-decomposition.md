## Functional Graph の木への分解

各頂点の出次数が 1 のグラフを、各連結成分の閉路から一辺を外し、仮想根 `N` を加えた根付き木へ変換する。`namori.hpp` の `Namori` とは別の実装。

- `FunctionalGraph<T>(n, adj, w)`: 頂点 `i` から `adj[i]` へ重み `w[i]` の辺を張る。`adj` と非空の `w` の長さは `n`。
- `FunctionalGraph<T>(n, g)`: 各連結成分に閉路がちょうど一つある無向グラフから構築する。
- `to[v]`, `weight[v]`: 元の有向辺の行き先と重み。
- `g`: 仮想根を含む、親から子へ向く木。外した閉路辺は `to` と `weight` で参照する。
- `represent[v]`: 同じ連結成分を代表する、仮想根の直下の頂点。
- `get_loops()`: 各閉路の頂点を `to` の向きに並べて返す。
- `get_loops_with_weight()`: `(頂点, その頂点から次への辺の重み)` の閉路列。

重み省略時は 1。ただし配列版コンストラクタの省略値が `vector<int>{}` なので、`T` が `int` 以外なら空の `vector<T>{}` を明示する。仮想根からの辺の重みは二つのコンストラクタで異なるため、元のグラフの距離としては使用しない。

構築は $O(n\alpha(n))$、閉路取得は出力サイズに比例、領域は $O(n)$。

#### 実装・検証

- [実装](../../graph/functional-graph.hpp)
- [検証: aoj-2891-2.test.cpp](../../verify/verify-aoj-other/aoj-2891-2.test.cpp)
- [検証: yuki-1254-2.test.cpp](../../verify/verify-yuki/yuki-1254-2.test.cpp)
