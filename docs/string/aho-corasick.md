## Aho–Corasick 法

`AhoCorasick<X=26,margin='a',heavy=false>` に非空のパターンを `add(s,id)` で登録し、`build()` を一度呼ぶ。その後パターンを追加しない。

`match(text)` は重なりを含む出現数を返す。`heavy=false` では全パターンの出現数の総和、`true` では `unordered_map<int,long long>` による ID ごとの出現数。`move` で状態を進め、`count(pos)` でその状態で終わるパターン数を得ることもできる。

通常版の構築は節点数 $M$ に対して $O(MX)$、照合は期待 $O(|text|)$。heavy 版は各状態の一致 ID を保持するため、構築・照合にその総量が加わる。空パターンや文字集合外の入力には使用しない。

#### 実装・検証

- [実装](../../string/aho-corasick.hpp)
- [検証: yuki-0430-2.test.cpp](../../verify/verify-yuki/yuki-0430-2.test.cpp)
- [検証: yuki-0430.test.cpp](../../verify/verify-yuki/yuki-0430.test.cpp)
- [検証: yuki-1269.test.cpp](../../verify/verify-yuki/yuki-1269.test.cpp)
