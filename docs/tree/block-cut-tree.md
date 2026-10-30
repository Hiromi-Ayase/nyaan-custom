## Block-Cut Tree

`BlockCutTree<G>(g)` は二重頂点連結成分と関節点を頂点とする無向の縮約森を `aux` に構築する。

`id(v)` は元頂点の対応先、`is_arti(v)` は関節点判定、`arti()` は関節点数。関節点の番号が先に並び、その後に成分が並ぶ。`operator[]` で縮約森の隣接リストを参照する。

自己ループ・多重辺のない無向グラフを想定。孤立点は成分に含まれず `id(v)==-1` となる。`build` はコンストラクタが呼ぶので再実行しない。時間・領域 $O(V+E)$。

#### 実装・検証

- [実装](../../tree/block-cut-tree.hpp)
- [検証: aoj-3022.test.cpp](../../verify/verify-aoj-other/aoj-3022.test.cpp)
- [検証: yuki-1326.test.cpp](../../verify/verify-yuki/yuki-1326.test.cpp)
