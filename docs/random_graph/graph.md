## 標準隣接リストの辺列変換・出力

`random_graph` 名前空間の関数に、`vector<vector<pair<int, T>>>` をそのまま渡す。各要素は `(行き先, 重み)`。専用のグラフ構造体や辺番号は使わない。

無向グラフは両方向の隣接要素を持つことが前提。自己ループも同じ重みで2回登録する。多重辺は本数を保ち、自己ループは隣接順によらず同じ重みの2要素を1本として扱う。

- `edge_list(g, directed=false)`: `(始点, 終点, 重み)` の `vector<tuple<int,int,T>>` を返す。無向の場合は始点が終点以下の辺を1本ずつ返す。有向の場合は各隣接要素をそのまま出力する。
- `edge_count(g, directed=false)`: 辺数。無向の場合は隣接要素数の半分。
- `adjacent_matrix(g)`: `vector<vector<T>>` を返す。隣接リストの向きをそのまま使い、辺なしは0、多重辺は最後の重みで上書きする。
- `print_matrix(os, g)`: 行列を空白区切りで出力する。
- `print_edges(os, g, weighted=false, directed=false, origin_0=false)`: 辺列を出力する。既定は頂点番号1始まり。`weighted=true` なら重みも出力する。
- `print(os, g, weighted=false, directed=false, origin_0=false)`: 最初に頂点数・辺数を出力し、その後に辺列を出力する。

辺の出力順は始点の昇順、各行内では隣接リストの順。辺数取得は $O(V+E)$、辺列化・出力は自己ループがなければ $O(V+E)$、自己ループの重み別管理を含めた上界は $O(V+E\log(E+1))$。行列化は $O(V^2+E)$。

#### 実装・検証

- [実装](../../random_graph/graph.hpp)
- [Verify: generation.cpp](../../tests/unit/random_graph/generation.cpp)
