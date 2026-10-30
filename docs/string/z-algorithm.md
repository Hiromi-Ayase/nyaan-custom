## Z algorithm

`z_algorithm(s)` は `s` 全体と接尾辞 `s[i:]` の共通接頭辞長を各 `i` について返す。非空なら `result[0] == s.size()`、空なら空配列。

添字アクセスと等値比較が可能な文字列・配列に使える。時間・領域は $O(n)$。

#### 実装・検証

- [実装](../../string/z-algorithm.hpp)
- [検証: yosupo-z-algorithm.test.cpp](../../verify/verify-yosupo-string/yosupo-z-algorithm.test.cpp)
