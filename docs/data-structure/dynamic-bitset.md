## 動的サイズの BitSet

`BitSet(n)` は長さ `n`、初期値 0 のビット列。`operator[]`、`test(i)`、`set(i)`、`reset(i)`、`flip(i)` で一点を $O(1)$ で操作する。

`a ^= b` は同じ長さの列の排他的論理和。`_Find_first/last()` は最初・最後の 1、`_Find_next(i)` は `i` より後、`_Find_prev(i)` は `i` より前の 1 を探す。見つからなければ前方探索は `n`、後方探索は `-1`。

XOR・探索の最悪時間と領域は $O(\lceil n/64\rceil)$。添字の範囲検査はしない。GCC 固有の最適化指定とビット演算組み込み関数を使用する。

#### 実装・検証

- [実装](../../data-structure/dynamic-bitset.hpp)
