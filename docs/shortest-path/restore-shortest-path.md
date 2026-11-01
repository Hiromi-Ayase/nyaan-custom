## 距離配列からの最短路復元

`restore_shortest_path(g, d, S, G)` は重み付きグラフと始点 `S` からの最短距離配列 `d` を受け取り、`S` から `G` への頂点列を返す。

逆辺を構築し、`d[u] + cost(u,v) == d[v]` となる未訪問の前頂点を選んでさかのぼる。

#### 前提と制約

`G` が到達可能で `S != G` であることが必要。前頂点が見つからない場合の失敗処理はなく、負の添字へアクセスする。正の辺重みなら距離が厳密に減少するため安全に復元できるが、重み 0 の閉路を含む場合は貪欲な選択が行き詰まることがある。一般の非負重みでは、親を記録する `dijkstra_restore` を用いる方が扱いやすい。

時間・追加領域は $O(V+E)$。

#### 実装・検証

- [実装](../../shortest-path/restore-shortest-path.hpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
