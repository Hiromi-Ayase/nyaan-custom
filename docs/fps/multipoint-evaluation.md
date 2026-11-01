## 多項式の多点評価

`MultipointEvaluation(f, xs)` は多項式 `f` の値 `f(xs[i])` を、点の入力順に返す。係数は低次順。点の重複は許され、空の多項式の値は全て `0`。

`ProductTree<mint>(xs)` は $\prod_i(x-xs[i])$ の積の木を作る。同じ点列で繰り返し評価する場合、`InnerMultipointEvaluation(f,xs,ptree)` で木を再利用できる。木は `xs` の参照を持つので、点列の寿命を木より長くし、内容を変更しない。

積の木で剰余を取りながら分割する。FPS の積・除算を提供するバックエンドが必要で、NTT 向けと任意法向けの両方の構築経路がある。

点数と多項式長が同程度の $N$ なら時間 $O(N\log^2 N)$、領域 $O(N\log N)$。短い剰余では各点の直接評価に切り替える。

#### 実装・検証

- [実装](../../fps/multipoint-evaluation.hpp)
- [Verify: evaluation.cpp](../../tests/unit/fps/evaluation.cpp)
