## 木の重心

`centroid(g)` は無向木の重心を頂点番号の配列で返す。重心を削除した各成分の最大サイズは頂点数の半分以下になる。通常、結果は一頂点または隣接する二頂点。

非空・連結・閉路なしの木を渡す。重み付き隣接リストでも重みは使用しない。明示スタックによる探索で時間・領域 $O(n)$。

#### 実装・検証

- [実装](../../tree/centroid.hpp)
- [Verify: centroids-and-distances.cpp](../../tests/unit/tree/centroids-and-distances.cpp)
