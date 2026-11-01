## 多項式と集合冪級数の合成

`polynomial_composite_set_power_series<mint,MAX=21>(n,f,g)` は多項式 `f` に集合冪級数 `g` を代入した係数列を返す。乗算は部分集合畳み込み。`0 <= n <= MAX` とし、`g` は少なくとも空集合係数を持つ必要がある。

`g[0] != 0` なら Taylor shift して定数項を除き、`f` を `n+1` 項、`g` を `2^n` 項にそろえる。階乗・逆階乗と FPS の演算が利用できる型を用いる。集合部分の時間は $O(n^2 2^n)$。

現在の include 先 `fps/taylor-shift.hpp` は存在しない。対応する実装は `fps/fps-taylor-shift.hpp` なので、利用にはこの依存の修正が必要。

#### 実装・検証

- [実装](../../set-function/polynomial-composite-set-power-series.hpp)
- [Verify: series.cpp](../../tests/unit/set-function/series.cpp)
