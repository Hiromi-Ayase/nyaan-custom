## ダイクストラ法(Skew Heap)

ダイクストラ法の定数倍高速化ライブラリ。

#### 概要

ダイクストラ法のヒープにSkew Heap(ねじれヒープ)を使用することで最小値の取得にかかる時間計算量を高速化したライブラリ。

#### 使い方

- `dijkstra(g, start = 0)`: sを始点としたダイクストラ法を行い、計算結果を返す。

#### 実装・検証

- [実装](../../shortest-path/dijkstra-skew-heap.hpp)
- [Verify: dijkstra-skew-heap.cpp](../../tests/unit/shortest-path/dijkstra-skew-heap.cpp)
