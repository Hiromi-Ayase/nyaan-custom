## 最小素因数表による素因数分解・約数列挙

テンプレート引数 `MAX` までの最小素因数表を初回に作り、繰り返し利用する。

- `osak<MAX>(n)`: 重複を含む素因数の昇順列。
- `osak_table<MAX>(n)`: `(素数, 指数)` の列。
- `osak_divisors<MAX>(n)`: 約数を昇順に列挙する。0 は空、1 は `{1}`。

`1 <= n <= MAX` を基本とする。前処理 $O(MAX)$、因数分解 $O(\log n)$、約数列挙は約数数 $d$ に対し $O(d\log d)$。各テンプレート・関数の static 表が別々に確保される。

#### 実装・検証

- [実装](../../prime/osak.hpp)
- [検証: factorize.test.cpp](../../verify/verify-unit-test/factorize.test.cpp)
- [検証: osak.test.cpp](../../verify/verify-unit-test/osak.test.cpp)
