## ダイクストラ法(Radix Heap)

ダイクストラ法の定数倍高速化ライブラリ。

#### 概要

ダイクストラ法のヒープに[Radix Heap(基数ヒープ)](https://nyaannyaan.github.io/library/data-structure/radix-heap.hpp)を使用することで最小値の取得にかかる時間計算量を高速化したライブラリ。

#### 使い方

`g` は `vector<vector<pair<int, T>>>`。要素は `(行き先, 重み)` で、入力は変更しない。距離の加算が `T` に収まること。重みは非負の整数とする。

- `dijkstra_radix_heap(g, start = 0)`: sを始点としたダイクストラ法を行い、計算結果を返す。

#### 実装・検証

- [実装](../../shortest-path/dijkstra-radix-heap.hpp)
- [Verify: weighted.cpp](../../tests/unit/shortest-path/weighted.cpp)
