# ローカルユニットテスト

各 `unit/**/*.cpp` は独立した C++17 プログラムです。標準ライブラリと検証対象のヘッダを読み込み、同じファイル内の素朴な参照実装・全探索・既知の境界ケースと照合します。共通のテストヘッダ、テストフレームワーク、問題データのダウンロードは使いません。

CMake 3.20 以上と GCC（C++17 対応）、x86-64 Linux 環境（AVX2・BMI2・LZCNT 対応CPU）を用意し、ライブラリのルートで次のように実行します。CMake のインストール方法は問いません。

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j 4
ctest --test-dir build -j 4 --output-on-failure
ctest --test-dir build -R z-algorithm --output-on-failure
```

テストは正常終了で成功、assertion failure・異常終了・時間超過で失敗します。CMake は Release ビルドでも `assert` を有効にします。ランダムケースはテストごとに固定シードを使います。失敗した場合は CTest のログに示されるソース行を参照し、同じテストを再実行できます。

範囲外アクセスや未定義動作は、AddressSanitizer・UBSanを有効にした別ビルドで検査できます。

```sh
cmake -S . -B build-sanitized -DCMAKE_BUILD_TYPE=Release -DNYAAN_ENABLE_SANITIZERS=ON
cmake --build build-sanitized -j 4
ctest --test-dir build-sanitized -j 4 --output-on-failure
```

Sanitizerが問題を検出すると、そのテストは直ちに失敗します。終了時まで節点プールを保持する競技プログラミング用の実装があるため、CTestではLeakSanitizerによるメモリリーク検査を無効にしています。範囲外アクセス・解放後のアクセス・未定義動作の検査は有効です。CIでも通常ビルドとSanitizerビルドの両方を実行します。

索引の363ヘッダを179個のテストで検証します。関連するヘッダは同じプログラム内で検証することがあります。CMakeの構成時に、索引の全ヘッダにテストがあること、各ドキュメントのVerifyリンクが登録済みのテストを指すことを検査します。

各ソースの `// Verify: ...` は直接検証するヘッダを示します。ヘッダの include が通ることだけでは検証扱いにせず、各対象の機能を実際に呼び出して結果を照合します。

テストコードでは `for`・`while`・`if` の本体を必ず `{}` で囲み、処理を1行に詰め込まず、準備・参照計算・照合のまとまりを空行で区切ります。カンマ演算子で複数の操作をつなげず、異なる役割の変数の宣言も分けます。ファイル冒頭には検証内容と境界ケースを書き、重要な `assert` の直前にも、何を何と比較するかを日本語のコメントで説明します。

書式設定は `tests/.clang-format` に置いてありますが、テストのビルド・実行にフォーマッタは不要です。
