## 入出力・乱数・タイマーの一括 include

`fastio.hpp`, `rng.hpp`, `timer.hpp` をまとめて読み込むヘッダ。`rd`, `wt`, `wtn`、乱数関数、`Timer` が利用可能になる。

競技用テンプレートの `main` は定義しない。各機能の前提・副作用は対応する個別ドキュメントを参照する。

#### 実装・検証

- [実装](../../misc/all.hpp)
- [Verify: fastio.cpp](../../tests/unit/misc/fastio.cpp)
