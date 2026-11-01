## 離散対数

`mod_log(a, b, p)` は $a^x\equiv b\pmod p$ を満たす最小の非負整数 `x` を返す。解がなければ `-1`。

`p` は正の整数で、素数でなくてもよい。`a`, `b` は負でも剰余へ正規化する。底と法の GCD を取り除いた後、baby-step giant-step 法で探索する。`p = 1` では `0`。

入力・途中の積・平方が符号付き 64 bit に収まる必要があり、全ての 64 bit の法を扱えるわけではない。時間・領域は $O(\sqrt p)$（ハッシュ表の操作は期待定数時間）。

#### 実装・検証

- [実装](../../modulo/mod-log.hpp)
- [Verify: mod-log.cpp](../../tests/unit/modulo/mod-log.cpp)
