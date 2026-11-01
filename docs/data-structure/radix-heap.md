## Radix Heap

#### 概要

Radix Heap(基数ヒープ)とは、単調順位ヒープ(追加した値が最後に取り出した値以上である必要があるヒープ)の一種である。`std::priority_queue`と比べて定数倍が軽いことからDijkstra法に用いて定数倍高速化に使用される。

キーは非負とし、符号なし型の最大値も使用できる。最大値の重複挿入にも対応する。`pop()` は非空のときに呼ぶ。

#### 使い方

- `RadixHeap<Key, Val>()`: コンストラクタ。`Key`は整数型のみを取る。
- `push(Key, Val)`: ヒープにpushする。
- `pop()`: ヒープの要素のうち最小のものをpopして返す。
- `size()`: ヒープ内の要素数を返す。
- `empty()`: ヒープが空かどうかを返す。

#### 実装・検証

- [実装](../../data-structure/radix-heap.hpp)
- [Verify: heaps.cpp](../../tests/unit/data-structure/heaps.cpp)
