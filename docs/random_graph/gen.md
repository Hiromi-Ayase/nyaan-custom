## 無向グラフのテスト生成

`UndirectedGraphGenerator(seed=0)`、またはグローバル `undirected` を使う。0 シードは時刻由来。`set_seed` で再現可能にできるが、乱数生成器はインスタンス間で共有する。

`tree/path/star/perfect/simple/namori/simple_sparse(n,weighted=false,w_min=1,w_max=1)` は木・パス・星・完全・ランダム単純・一閉路・疎グラフを生成する。返り値は `vector<vector<pair<int, long long>>>` で、各要素は `(行き先, 重み)`。無向辺の両方向を保持するため、そのままグラフアルゴリズムへ渡せる。重みは指定した閉区間。重みなし指定でも同じ型で、重みは1。`test(n,is_tree,...)` はこれらから方式を選ぶ。

`random_graph::print(cout, g, true)` で重みも出力できる。出力時の重みの有無は明示する。

namori は n>=2 が必要で多重辺を含み得る。simple は連結性を保証しない。木生成は $O(n\log n)$、完全・ランダム単純グラフは $O(n^2)$。用途に応じて形式を明示して選ぶ。

#### 実装・検証

- [実装](../../random_graph/gen.hpp)
- [Verify: generation.cpp](../../tests/unit/random_graph/generation.cpp)
