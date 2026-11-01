## 二進有理数による超現実数の表現

`SurrealNumber(p,q=0)` は `p / 2^q` を long long の二つ組で保持する。加減算・比較・符号反転・表示を提供し、`normalize` は 2 の因子を除く。

`child()` は数の二分木上の左右の子、`larger/smaller()` は現在値より大きい・小さい簡単な数、`reduce(l,r)` は開区間にある最も簡単な数を根から探索する。`l < r` が必要。

任意精度ではない。分母指数、分子のシフト・和が型に収まる範囲で使う。符号付き負値の左シフトを使う箇所があり、厳密な標準 C++ の移植性には制約がある。

#### 実装・検証

- [実装](../../game/surreal-number.hpp)
- [Verify: partisan-and-surreal.cpp](../../tests/unit/game/partisan-and-surreal.cpp)
