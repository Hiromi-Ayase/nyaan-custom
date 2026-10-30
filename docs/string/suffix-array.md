## Suffix Array と LCP（旧実装）

`SuffixArray sa(s)` は文字列の接尾辞を辞書順に並べる。**空の接尾辞を含む**ため `size()` は `s.size()+1`、`sa[0]` は元の文字列長となる。構築中は番兵を追加してから除去する。元の文字列は参照で保持し、その後変更しない。

`LCPArray lcp(sa)` の `LCP[i]` は `sa[i]` と `sa[i+1]` の共通接頭辞長。`StringSearch search(lcp)` で `ArbitaryLCP(i,j)` を取得できる。`find(t)` は一致する接尾辞の SA 上の**閉区間**を返し、未発見は `(-1,-1)`。検索は非空の元文字列を前提とする。

SA 構築 $O(n\log n)$、LCP 構築 $O(n)$、検索用の前処理 $O(n\log n)$、パターン検索 $O(|t|+\log n)$。`string-search.hpp` と `StringSearch` が衝突する。

#### 実装・検証

- [実装](../../string/suffix-array.hpp)
- [検証: yosupo-number-of-substrings.test.cpp](../../verify/verify-yosupo-string/yosupo-number-of-substrings.test.cpp)
- [検証: yosupo-suffix-array.test.cpp](../../verify/verify-yosupo-string/yosupo-suffix-array.test.cpp)
- [検証: yosupo-zalgo-suffixarray.test.cpp](../../verify/verify-yosupo-string/yosupo-zalgo-suffixarray.test.cpp)
