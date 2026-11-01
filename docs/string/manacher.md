## Manacher 法と回文列挙

`manacher(s)` の `r[i]` は位置 `i` を中心とする奇数長回文の半径（中心を含む）。対応する半開区間は `[i-r[i]+1, i+r[i])`。

`enumerate_palindromes(s)` は文字上・文字間の各中心について極大回文の半開区間を左から返す。文字間の空回文も含み、非空長 `n` に対し `2n-1` 個。`enumerate_leftmost_palindromes(s)[r]` は閉区間 `[l,r]` が回文となる最小の `l`。

列挙関数には非空入力が必要で、区切りに `value_type(-1)` を使うため元の要素にこの値を含めない。時間・領域は $O(n)$。

#### 実装・検証

- [実装](../../string/manacher.hpp)
- [Verify: manacher.cpp](../../tests/unit/string/manacher.cpp)
