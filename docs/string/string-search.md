## 接尾辞・部分列の LCP と辞書順比較

`StringSearch<Container>(s)` は ACL の Suffix Array と Sparse Table を構築する。非空の入力を渡し、参照される `s` を変更せず生存させる。

`lcp(i,j)` は接尾辞間、`lcp(a,b,c,d)` は半開部分列 `[a,b)` と `[c,d)` 間の共通接頭辞長。`strcmp` も同じ引数形式で、小さい・等しい・大きいを `-1,0,1` で返す。区間は pair でも渡せる。

空区間でも始点に `s.size()` を渡すと内部 assert に失敗するため、末尾の空区間は呼び出し側で処理する。前処理・領域は $O(n\log n)$、各問い合わせは $O(1)$。旧版 `suffix-array.hpp` と同時に include しない。

#### 実装・検証

- [実装](../../string/string-search.hpp)
- [検証: string-search.test.cpp](../../verify/verify-unit-test/string-search.test.cpp)
- [検証: yuki-2231.test.cpp](../../verify/verify-yuki/yuki-2231.test.cpp)
