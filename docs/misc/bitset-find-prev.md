## bitset の後方ビット探索

`Bitset<Nb>` は `std::bitset<Nb>` を継承し、`_Find_prev(i)`（`i` 未満の最大の 1 ビット位置）と `_Find_last()` を追加する。未発見は `-1`、探索の `i` は `[0,Nb]` に収める。

最悪時間 $O(\lceil Nb/64\rceil)$。libstdc++ の内部配置を 64 bit 配列として読み替える実装に依存し、移植可能な標準 C++ の API ではない。

#### 実装・検証

- [実装](../../misc/bitset-find-prev.hpp)
- [Verify: basic-utilities.cpp](../../tests/unit/misc/basic-utilities.cpp)
