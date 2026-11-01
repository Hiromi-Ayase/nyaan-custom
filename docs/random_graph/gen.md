## 無向グラフのテスト生成

`UndirectedGraphGenerator(seed=0)`、またはグローバル `undirected` を使う。0 シードは時刻由来。`set_seed` で再現可能にできるが、乱数生成器はインスタンス間で共有する。

`tree/path/star/perfect/simple/namori/simple_sparse(n,weighted=false,w_min=1,w_max=1)` は木・パス・星・完全・ランダム単純・一閉路・疎グラフを生成する。重みは指定した閉区間。`test(n,is_tree,...)` はこれらから方式を選ぶ。

namori は n>=2 が必要で多重辺を含み得る。simple は連結性を保証しない。木生成は $O(n\log n)$、完全・ランダム単純グラフは $O(n^2)$。用途に応じて形式を明示して選ぶ。

#### 実装・検証

- [実装](../../random_graph/gen.hpp)
- [Verify: generation.cpp](../../tests/unit/random_graph/generation.cpp)
