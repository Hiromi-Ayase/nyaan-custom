## 疎な連立一次方程式

`LinearEquation_hashmap(A, b, upper = -1)` は各行を `HashMap<int, mint>` で表した方程式 `A*x = b` を解く。キーは列番号、値は係数。解があれば自由変数を `0` にした特殊解、なければ空配列を返す。

このヘッダ自身は依存する型を読み込まない。使用前に `mint` と `HashMap` を定義する。変数数を `b.size()` から決める実装なので、行数・変数数・右辺サイズが一致する正方の系を渡す。係数は非零要素で割れる体を仮定する。

現実装では `if (upper = -1)` という代入があり、引数 `upper` は常に変数数で上書きされる。帯幅制限としては機能しない。消去中に非零成分が増えることがあり、最悪では通常の密行列と同じ $O(n^3)$ 時間、$O(n^2)$ 領域が必要。

#### 実装・検証

- [実装](../../matrix/linear-equation-hashmap.hpp)
- [Verify: sparse-equation.cpp](../../tests/unit/matrix/sparse-equation.cpp)
