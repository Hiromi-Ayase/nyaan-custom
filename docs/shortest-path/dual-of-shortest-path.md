## 差分制約（最短路問題の双対）

`f(j) <= f(i) + c` という差分制約を Bellman–Ford 型の緩和で解く。

- `Dual_of_Shortest_Path<T> solver(n)`: `n` 個の変数を用意する。
- `add_edge(i, j, c)`: 上記の不等式を登録する。
- `solve()`: 全変数を 0 から緩和する。実行可能なら制約を満たす値の配列、矛盾する負閉路があれば空列を返す。
- `solve(start)`: `start` のみ 0、他を大きな値から開始する。全変数へ到達でき、制約が実行可能なら `f(t)-f(start)` の最大値を返す。

`solve(start)` は到達不能頂点からの緩和をスキップしない。そのため到達不能成分の値を厳密な無限大や最適値として解釈しない。可解性判定には引数なしの `solve()` を使う。

時間は $O(VE)$、制約保存を含む領域は $O(V+E)$。負の値と中間計算を表せる `T` を使う。

#### 実装・検証

- [実装](../../shortest-path/dual-of-shortest-path.hpp)
- [Verify: negative-edges.cpp](../../tests/unit/shortest-path/negative-edges.cpp)
