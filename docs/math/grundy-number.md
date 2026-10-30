## DAG 上の Grundy 数

`GrundyNumber(g)` は有向非循環グラフの各頂点について、遷移先の Grundy 数の mex を返す。出次数 0 の頂点は 0。

閉路がある場合は空配列。空グラフの返り値も空。独立なゲームを合成する場合は Grundy 数の XOR を取り、0 が後手必勝を表す。

トポロジカル順の逆順で計算し、時間・領域は $O(V+E)$。

#### 実装・検証

- [実装](../../math/grundy-number.hpp)
- [検証: yuki-0103.test.cpp](../../verify/verify-yuki/yuki-0103.test.cpp)
