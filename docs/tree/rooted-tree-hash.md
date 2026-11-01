## 根付き木のハッシュ

入力の隣接リストは `vector<vector<int>>` と `vector<vector<pair<int, T>>>`（行き先・重み）の両方に対応する。木の構造の計算では重みを無視する。

`RootedTreeHash<G>(g,root=0)` は子の順序に依存しない根付き部分木ハッシュを計算する。`hash[v]` は v 以下の形、`depth[v]` は根からの距離ではなく部分木の高さ。

非空の無向木を渡す。頂点ラベル・辺重みはハッシュに含めない。同じ G 型では高さごとの乱数を共有するので、その範囲で比較できる。異なる形でもハッシュ衝突の可能性がある。

再帰 DFS により時間・領域 $O(n)$。元のグラフは参照で保持される。

#### 実装・検証

- [実装](../../tree/rooted-tree-hash.hpp)
- [Verify: hashes.cpp](../../tests/unit/tree/hashes.cpp)
- [Verify: weighted-containers.cpp](../../tests/unit/tree/weighted-containers.cpp)
