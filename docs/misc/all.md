## 入出力・乱数・タイマーの一括 include

`fastio.hpp`, `rng.hpp`, `timer.hpp` をまとめて読み込むヘッダ。`rd`, `wt`, `wtn`、乱数関数、`Timer` が利用可能になる。

競技用テンプレートの `main` は定義しない。各機能の前提・副作用は対応する個別ドキュメントを参照する。

#### 実装・検証

- [実装](../../misc/all.hpp)
- [検証: arbitrary-ntt-mod18446744069414584321.test.cpp](../../verify/verify-unit-test/arbitrary-ntt-mod18446744069414584321.test.cpp)
- [検証: bigint2.test.cpp](../../verify/verify-unit-test/bigint2.test.cpp)
- [検証: bigint3.test.cpp](../../verify/verify-unit-test/bigint3.test.cpp)
