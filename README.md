競技プログラミング用ライブラリ

[ドキュメント索引](docs/README.md)

[CTestによるローカルユニットテスト](tests/README.md)

g++, c++17での使用を想定しています。(一部のライブラリはavx2対応の環境でのみ動作します。)

[Nyaan's Library](https://nyaannyaan.github.io/library/)の私的カスタマイズ版です

提出用にローカルヘッダを展開する場合は `python3 bundle.py main.cpp > submission.cpp` を使えます（Python 3.9以上、追加パッケージ不要）。必要なら `-I include_directory` で探索先を追加できます。
