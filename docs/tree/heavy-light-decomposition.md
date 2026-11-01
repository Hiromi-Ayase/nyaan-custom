## Heavy Light Decomposition(重軽分解)

入力の隣接リストは `vector<vector<int>>` と `vector<vector<pair<int, T>>>`（行き先・重み）の両方に対応する。木の構造の計算では重みを無視する。

#### 概要

Heavy Light Decomposition(重軽分解、HLDec)とは、木のパスをheavy pathとlight pathに分けて管理するデータ構造である。

HLDecの特長は「任意のパスを$\rm{O}(\log N)$本の列に分解する」という点である。木をHLDecで管理することで木に対する問題を列に対する問題として処理することができるため、「パス上の頂点の持つ値を同時に更新する」といった木上のパスに関するクエリを容易に処理することが出来るようになる。

#### 使い方

- `HeavyLightDecomposition(g, root=0)`:`root`を根とした重軽分解を構築する。$\mathrm{O}(N)$
- `idx(i)`: 頂点iのオイラーツアー順を`pair(down, up)`の形で返す。$\mathrm{O}(1)$
- `path_query(u, v, vertex, f)`: **可換な**パスクエリを処理する。$\mathrm{O}(\log^2N)$
- `path_noncommutative_query(u, v, vertex, f)`: **非可換な**パスクエリを処理する。$\mathrm{O}(\log^2N)$
- `subtree_query(u, vertex, f)`: 部分木クエリを処理する。$\mathrm{O}(\log^N)$
- `lca(u, v)`: uとvの最小共通祖先(LCA)を返す。$\mathrm{O}(\log^N)$

#### 実装・検証

- [実装](../../tree/heavy-light-decomposition.hpp)
- [Verify: queries.cpp](../../tests/unit/tree/queries.cpp)
- [Verify: weighted-containers.cpp](../../tests/unit/tree/weighted-containers.cpp)
