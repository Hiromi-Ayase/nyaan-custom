## ダイクストラ法

ダイクストラ法を$\mathrm{O}(E \log V)$で行うライブラリ。

#### 概要

ダイクストラ法とは負辺の無い有向グラフでの単一始点最短経路を$\mathrm{O}(E \log V)$で計算するアルゴリズムである。[基数ヒープ](https://nyaannyaan.github.io/library/shortest-path/dijkstra-radix-heap.hpp)やフィボナッチヒープを用いた高速化も知られている。

#### 使い方

`g` は `vector<vector<pair<int, T>>>`。要素は `(行き先, 重み)` で、入力は変更しない。距離の加算が `T` に収まること。重みは非負とする。

- `dijkstra(g, start = 0)`: sを始点としたダイクストラ法を行い、sからの距離(到達できない場合`-1`)が格納された配列を返す。

#### 実装・検証

- [実装](../../shortest-path/dijkstra.hpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
