## 頂点を基礎とする Static Top Tree

入力の隣接リストは `vector<vector<int>>` と `vector<vector<pair<int, T>>>`（行き先・重み）の両方に対応する。木の構造の計算では重みを無視する。

固定木の DP を頂点変更に追従させる。先に `HeavyLightDecomposition<G> hld(g)` を構築し、`DPonStaticTopTreeVertexBased` に hld と次のコールバックを渡す。

- `vertex(i) -> Path`: 単一頂点の情報。
- `compress(parent_path,child_path) -> Path`: 縦のパスを結合。
- `rake(a,b) -> Point`: 横の部分木を結合。
- `add_edge(path) -> Point`: 子のパスを親へ渡す情報に変換。
- `add_vertex(point,i) -> Path`: 子の集合に頂点 i を追加。

外部の頂点情報を変えて `update(i)` を呼ぶと祖先を再計算する。`get()` は固定根の全体結果。コールバックは分割方法に依存しない結果になるよう設計する。hld を生存させる。

結合が定数時間なら更新 $O(\log n)$、取得 $O(1)$、領域 $O(n)$。構造構築は再帰的な配列分割を含め保守的に $O(n\log n)$。

#### 実装・検証

- [実装](../../tree/static-top-tree-vertex-based.hpp)
- [Verify: static-top-trees.cpp](../../tests/unit/tree/static-top-trees.cpp)
- [Verify: weighted-containers.cpp](../../tests/unit/tree/weighted-containers.cpp)
