## 最長増加部分列の復元

`longest_increasing_sequence(a)` は狭義単調増加部分列のうち最長のものを、値ではなく元配列の添字列で返す。同値の要素を連続して選ぶことはない。

返却添字は元の順に並ぶ。空入力では内部で `dp.back()` を参照するため、呼び出し側で空を処理する。

時間 $O(n\log n)$、領域 $O(n)$。

#### 実装・検証

- [実装](../../dp/longest-increasing-sequence.hpp)
- [検証: yosupo-longest-increasing-sequence.test.cpp](../../verify/verify-yosupo-math/yosupo-longest-increasing-sequence.test.cpp)
