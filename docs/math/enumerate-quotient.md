## 整数除算の商をまとめて列挙

`enumerate_quotient(N,f)` は `floor(N/x)` が等しい範囲ごとに `f(q,l,r)` を呼ぶ。対象は正の x で、範囲は **`l < x <= r`**。

商 q の小さい順に走査する。N は非負の long long に収まる値を想定し、N=0 では何も呼ばない。$O(\sqrt N)$ 回のコールバック、追加領域 $O(1)$。

内部で `isqrt` を使うので、その乗算オーバーフローの制約も受ける。

#### 実装・検証

- [実装](../../math/enumerate-quotient.hpp)
- [Verify: floor-and-quotient.cpp](../../tests/unit/math/floor-and-quotient.cpp)
