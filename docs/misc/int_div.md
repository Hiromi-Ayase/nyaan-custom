## 符号付き整数の除算と丸め

`floor(a,b)`, `under(a,b)`, `ceil(a,b)`, `over(a,b)` はそれぞれ `a/b` 以下・未満・以上・超過となる境界整数を `long long` で返す。負の被除数・除数にも対応する。

除数は非零とし、符号反転や除算がオーバーフローする `LLONG_MIN` の境界は避ける。`modulo(a,b)` は正の `b` に対して `[0,b)` の剰余を返す（assert は `b==0` を排除しないので呼び出し側で保証する）。各操作 $O(1)$。

#### 実装・検証

- [実装](../../misc/int_div.hpp)
- [Verify: basic-utilities.cpp](../../tests/unit/misc/basic-utilities.cpp)
