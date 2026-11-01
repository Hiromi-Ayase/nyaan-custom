## 整数・pair・列のハッシュ関数

`internal::hash_function(x)` は整数、pair、iterator 型を持つコンテナを再帰的に 64 bit 整数へ写す。`HashObject<Key>` は標準 unordered コンテナへ渡せる関数オブジェクト。

整数は定数時間、pair は両要素の計算量の和、列は全要素に比例する。型ごとの static シードを使うため、実行をまたいだ永続 ID には使用しない。

衝突はあり得るのでキーの等値比較と組み合わせる。整数を 64 bit へ変換するため、128 bit 整数の上位ビットは整数ハッシュだけでは区別されない。

#### 実装・検証

- [実装](../../internal/internal-hash-function.hpp)
- [Verify: hash.cpp](../../tests/unit/internal/hash.cpp)
