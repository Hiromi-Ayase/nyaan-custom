## 下位集合・上位集合の列挙

`enumerate_subset(b)` は非負ビットマスク `b` の部分集合を降順で返す。空集合 0 と `b` 自身を含む。

`enumerate_superset(b,n)` は n 要素の全集合内で `b` を含む集合を昇順で返す。`0 <= b < 2^n` とし、`1<<n` が符号付き int に収まる範囲で使う。

時間・出力領域はそれぞれ $O(2^{popcount(b)})$、$O(2^{n-popcount(b)})$。

#### 実装・検証

- [実装](../../set-function/enumerate-set.hpp)
- [検証: aoj-itp2-11-b.test.cpp](../../verify/verify-aoj-itp/aoj-itp2-11-b.test.cpp)
- [検証: aoj-itp2-11-c.test.cpp](../../verify/verify-aoj-itp/aoj-itp2-11-c.test.cpp)
- [検証: yuki-3024.test.cpp](../../verify/verify-yuki/yuki-3024.test.cpp)
