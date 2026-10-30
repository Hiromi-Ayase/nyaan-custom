## Trie

`Trie<X=26,margin='a'>` は文字 `margin` から `margin+X-1` の文字列を扱う。根の番号は 0。

`add(s,id)` は文字列と ID を登録する。`find(s)` は対応する節点番号、道がなければ `-1`。接頭辞に対応する節点でも成功するため、登録語かどうかは `idx(pos)`（最後の ID、未登録は `-1`）や `idxs(pos)`（登録 ID 列）で判定する。`move(pos,c)` は一文字遷移。

追加・検索は文字列長に比例し、新規節点の初期化は各 $O(X)$。領域は全節点数を $M$ として $O(MX)$。

#### 実装・検証

- [実装](../../string/trie.hpp)
- [関連検証（間接使用）: yuki-0430-2.test.cpp](../../verify/verify-yuki/yuki-0430-2.test.cpp)
- [関連検証（間接使用）: yuki-0430.test.cpp](../../verify/verify-yuki/yuki-0430.test.cpp)
- [関連検証（間接使用）: yuki-1269.test.cpp](../../verify/verify-yuki/yuki-1269.test.cpp)
