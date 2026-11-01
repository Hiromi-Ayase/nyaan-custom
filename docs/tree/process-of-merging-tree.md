## 併合過程を表す木

`process_of_merging_tree(es)` は辺を入力順に処理し、異なる成分の併合ごとに補助頂点を作る。Kruskal の併合木が必要なら、呼び出し前に辺を重み順にソートする（関数内ではソートしない）。

入力は `vector<tuple<int, int, T>>` で、要素は `(始点, 終点, 重み)`。返り値は `(親から子への vector<vector<pair<int, T>>>, 補助頂点の重み列, 根番号)`。隣接要素は `(子, 重み)`。頂点数 n は辺の最大番号から推定し、元頂点は `[0,n)`、補助頂点は `[n,2n-1)`、根は `2n-2`。補助頂点 i の重みは配列の `i-n` 番目。

全頂点が最終的に連結になることが必要。辺列から分からない孤立点は指定できない。時間 $O(E\alpha(n))$、領域 $O(n)$。UnionFind のヘッダは内部で読み込む。

#### 実装・検証

- [実装](../../tree/process-of-merging-tree.hpp)
- [Verify: constructions.cpp](../../tests/unit/tree/constructions.cpp)
