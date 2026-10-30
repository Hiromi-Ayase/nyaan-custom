## 乗法的関数の値の列挙

`enamurate_multiplicative_function<T, f>(n).run()` は乗法的関数の値 `a[0..n]` を返す。`n >= 1` とし、`a[0] = 0`, `a[1] = 1`。

テンプレート引数 `f` は `T f(int pc, int p, int c)` という関数ポインタで、`pc = p^c` における値を返す。異なる素数の寄与は積として組み合わされるため、任意の算術関数ではなく乗法的関数を指定する。クラス名の `enamurate` は実装通りの綴り。

素数表と素数冪の再帰列挙を使う。素数冪での評価が定数時間なら、時間は $O(n\log\log n)$ 以下、結果を含む領域は $O(n)$。値が `0` の枝を省略するため、係数型の零が積の吸収元であることが必要。

#### 実装・検証

- [実装](../../multiplicative-function/enamurate-multiplicative-function.hpp)
- [検証: mf.test.cpp](../../verify/verify-unit-test/mf.test.cpp)
