## ハッシュ重複を除いた上位 K 件

`Top_K<Data,get_hash>(K)` は `operator<` で小さい順に K 件を残す候補集合。`K > 0` とする。

`insert(d)` は同じハッシュなら小さい方だけを保持する。`get()` は候補を K 件以下に整理して vector への参照を返すが、ソートはしない。返却参照を直接変更するとハッシュ表との対応が壊れる。

ハッシュ衝突は同一状態と扱われる。2K 件ごとに nth_element で整理し、挿入は期待・償却 $O(1)$、整理は期待 $O(K)$、領域 $O(K)$。

#### 実装・検証

- [実装](../../marathon/top-k.hpp)
- [Verify: top-k-and-bandit.cpp](../../tests/unit/marathon/top-k-and-bandit.cpp)
