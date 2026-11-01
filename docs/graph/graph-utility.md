## グラフユーティリティ

重みなしグラフは `vector<vector<int>>`、重み付きグラフは `vector<vector<pair<int, T>>>` を使う。`pair` は `(行き先, 重み)`。入力は変更しない。

- `Depth(g, start=0)`: 重みなしグラフでは BFS による最短距離を返す。到達不能は `-1`。時間は $O(V+E)$。
- `Depth(g, start=0)`: 重み付きグラフでは木上の経路の重み和を返す。木または森を渡すこと。到達不能は `-1`、時間は $O(V+E)$。
- `Diameter(g)`: 非空の連結な木の直径を `((u, v), length)` として返す。重み付きでは辺重みが非負であること。時間は $O(V)$。
- `Path(g, u, v)`: 木の `u` から `v` へのパスを、両端を含む頂点列で返す。重み付きでも重みを無視して頂点列を求める。時間は $O(V)$。

### グラフの入力

入力は各問題の `main.cpp` で読み、標準コンテナへ直接追加する。重みなし隣接リストは行き先だけ、重み付き隣接リストは `(行き先, 重み)`、辺列は `(始点, 終点, 重み)` を格納する。

以下は1始まりの頂点番号で与えられる、重み付き無向グラフの入力例。自己ループも両方向として2回追加し、多重辺は別々の要素として保持する。有向グラフなら逆辺の追加を省く。

```cpp
int n;
int m;
cin >> n >> m;
vector<vector<pair<int, long long>>> g(n);
for (int i = 0; i < m; ++i) {
  int u;
  int v;
  long long weight;
  cin >> u >> v >> weight;
  --u;
  --v;
  g[u].emplace_back(v, weight);
  g[v].emplace_back(u, weight);
}
```

重みなしなら `vector<vector<int>>` に `g[u].push_back(v)` で追加する。辺列が必要なら `vector<tuple<int, int, long long>>` に `edges.emplace_back(u, v, weight)` で追加する。隣接行列は `vector<vector<T>>` を使い、辺がない場合の値と対角要素をアルゴリズムに合わせて初期化する。

### 旧APIからの変更

専用の辺構造体・グラフ型エイリアス・CSR格納クラスと、入力関数 `graph` / `wgraph` / `esgraph` / `adjgraph` は廃止した。隣接リストの辺は `auto [to, cost]`、辺列は `auto [from, to, cost]` で読み出す。

通常版と高速版を同時に include できるよう、高速版の関数名は `dijkstra_fast` / `dijkstra_restore_fast`、Skew Heap版は `dijkstra_restore_skew_heap` とした。`dijkstra_point` は従来どおり。各関数のグラフ引数は同じ重み付き隣接リストを使える。

#### 実装・検証

- [実装](../../graph/graph-utility.hpp)
- [Verify: utilities.cpp](../../tests/unit/graph/utilities.cpp)
