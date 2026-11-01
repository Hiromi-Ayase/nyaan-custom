## Prüfer 列からの木の復元

`pruefer_code(code)` は長さ n-2 の Prüfer 列から n 頂点の無向木の隣接リストを返す。n >= 3 とし、各要素は `[0,n)`。

`random_tree(n)` は乱数で Prüfer 列を作って木を生成し、n=0,1,2 も特別扱いする。乱数のシード規則は `misc/rng.hpp` に従う。

最小葉の集合を set で管理するため時間 $O(n\log n)$、領域 $O(n)$。

#### 実装・検証

- [実装](../../tree/pruefer-code.hpp)
- [Verify: constructions.cpp](../../tests/unit/tree/constructions.cpp)
