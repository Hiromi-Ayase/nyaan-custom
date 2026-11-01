## 連続する点からの 1 点補間

`lagrange_interpolation(y, x, C)` は `y[i] = f(i)` (`0 <= i <= N`) を満たす次数高々 `N` の多項式について `f(x)` を返す。`C` は `Binomial<mint>`。

`y` は非空、`x` は非負の `long long` とする。`x <= N` は配列から直接返す実装なので、負の `x` は渡せない。係数体で `0..N` が相異なり、`N!` が可逆であることが必要。

Lagrange の基底を前後の積で計算する。階乗表の準備後は時間 $O(N)$、追加領域 $O(N)$。既知の点への問い合わせは $O(1)$。

#### 実装・検証

- [実装](../../fps/lagrange-interpolation-point.hpp)
- [Verify: famous-series.cpp](../../tests/unit/fps/famous-series.cpp)
- [Verify: shifts.cpp](../../tests/unit/fps/shifts.cpp)
