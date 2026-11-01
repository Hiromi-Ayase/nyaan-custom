## 対数乱数の事前計算

`log_table` は固定 xorshift 列から `log(U)` に相当する値を 65536 個生成する。`table(i)` は `i & 65535` 番目の値を返す。

焼きなましの受理判定などで対数計算を省く用途。列は固定かつ周期的に再利用される。構築は 65536 回の対数計算、参照は $O(1)$、領域は double 65536 個。

#### 実装・検証

- [実装](../../marathon/log_table.hpp)
- [Verify: top-k-and-bandit.cpp](../../tests/unit/marathon/top-k-and-bandit.cpp)
