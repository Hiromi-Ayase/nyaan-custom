## 根のない木のハッシュ

入力の隣接リストは `vector<vector<int>>` と `vector<vector<pair<int, T>>>`（行き先・重み）の両方に対応する。木の構造の計算では重みを無視する。

`tree_hash(g)` は木の重心を根としたハッシュをソートして返す。重心が一つなら同じハッシュを二つ入れ、返却長は常に 2。

頂点番号や隣接リストの順序によらない形の比較に使う。ラベル・辺重みは考慮せず、非空の無向木を渡す。ハッシュ一致は衝突の可能性を含む。時間・領域 $O(n)$。

#### 実装・検証

- [実装](../../tree/tree-hash.hpp)
- [Verify: hashes.cpp](../../tests/unit/tree/hashes.cpp)
- [Verify: weighted-containers.cpp](../../tests/unit/tree/weighted-containers.cpp)
