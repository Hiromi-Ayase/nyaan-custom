## 競技プログラミング用テンプレート

標準ヘッダ、型・配列補助、ビット演算、入出力、デバッグ、ループマクロをまとめて読み込む。

このヘッダ自身が `int main()` を定義し、`Nyaan::solve()` を呼ぶ。利用側では `void Nyaan::solve() { ... }` を定義し、別の `main` を重ねて定義しない。

`using namespace std`、静的な入出力設定、GCC/x86 の intrinsic ヘッダを含む。単独 include を前提としない補助ヘッダは、このテンプレートの順序で読み込む。

#### 実装・検証

- [実装](../../template/template.hpp)
- [Verify: utilities.cpp](../../tests/unit/template/utilities.cpp)
