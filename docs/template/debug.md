## デバッグ表示

`trc(...)` は `NyaanDebug` 定義時、`trc2(...)` は `NyaanLocal` 定義時に、式の文字列と値を標準エラーへ出力する。無効時は引数を評価しない。

`DebugImpl::dump/trace` は整数・128 bit 整数・文字列・pair・コンテナを再帰的に表示する。`Nyaan::inf/infLL` の値は inf 表示になる。

`util.hpp` の型・定数と標準ヘッダに依存するため、通常は `template.hpp` から読み込む。出力時間は表示量に比例する。

#### 実装・検証

- [実装](../../template/debug.hpp)
- [Verify: utilities.cpp](../../tests/unit/template/utilities.cpp)
