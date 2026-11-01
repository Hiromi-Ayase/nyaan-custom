## 一次関数の合成

`Affine<mint>(a,b)` は `a*x+b`。既定値は恒等関数。`f(x)` で値を評価する。

積 `left * right` は **`right(left(x))`** を表す。`f(g)` は `f(g(x))`。Segment Tree の結合順を決めるときは、この積の向きに合わせる。

係数型の演算が定数時間なら構築・合成・評価も $O(1)$。

#### 実装・検証

- [実装](../../math/affine-transformation.hpp)
- [Verify: affine-and-gray.cpp](../../tests/unit/math/affine-and-gray.cpp)
