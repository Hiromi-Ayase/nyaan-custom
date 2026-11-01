## 型・配列・累乗の補助関数

`Nyaan` 名前空間に整数型 `ll/i64/u64/i128/u128`、vector 型別名、成分ごとに演算できる pair 型 `P` を用意する。

`amin/amax` は更新したかを bool で返す。`Max/Min/Sum` は配列集約（Sum は long long）。`lb/ub` はソート済み配列の境界添字。`mkrui` は累積和、`mkuni` はソート・重複除去、`mkord` は順列、`mkinv` は値から最後の位置への表、`mkiota/mkrev/nxp` は連番・反転・次順列。

`Power(a,n,I,f)` は非負指数の二分累乗で、乗算後に `f(T&)` を適用する。`product(a)` は各軸 `[0,a[i])` の直積を全列挙する。`Transpose/Rotate` は二次元配列の変換。`Rotate` の式は `clockwise=true` で行列添字上の反時計回りとなるため、必要な向きを確認して使う。

集約・逆表・回転など空入力を扱わない関数がある。通常は `template.hpp` から読み込む。

#### 実装・検証

- [実装](../../template/util.hpp)
- [Verify: utilities.cpp](../../tests/unit/template/utilities.cpp)
