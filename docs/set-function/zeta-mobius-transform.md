## 部分集合・上位集合のゼータ／Möbius 変換

長さ $2^n$ の配列を集合のビットマスクで添字付けする。

`subset_zeta_transform(f)` は `f[S] = Σ_{T⊆S} old[T]`、`superset_zeta_transform(f)` は `f[S] = Σ_{T⊇S} old[T]` に破壊的に変換する。それぞれの逆が `subset_mobius_transform`、`superset_mobius_transform`。

ゼータ変換には加算、逆変換には減算が必要。時間 $O(n2^n)$、追加領域 $O(1)$。

#### 実装・検証

- [実装](../../set-function/zeta-mobius-transform.hpp)
- [関連検証（間接使用）: set-function.test.cpp](../../verify/verify-unit-test/set-function.test.cpp)
