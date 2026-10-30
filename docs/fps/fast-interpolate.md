## 積の木による高速補間・多点評価

`SubproductTree<mint>(xs)` は評価点の積の木を前計算する。`multiEval(f)` は `f(xs[i])`、`interpolate(ys)` は `f(xs[i]) = ys[i]` を満たす次数が点数未満の多項式を返す。

点の配列は非空とし、補間では全ての点が係数体上で相異なる必要がある。`ys.size() == xs.size()`。係数は低次順で、返り値の評価値は入力の点と同じ順序。

NTT と原始根を直接使うので、対応する NTT 向け FPS バックエンドが必要。内部の最大変換長が法の制限に収まるようにする。内部バッファへのポインタを保持するため、構築後のオブジェクトを単純にコピーして利用しない。

点数と多項式の長さが同程度の $N$ なら、構築・評価・補間はそれぞれ $O(N\log^2 N)$、積の木は $O(N\log N)$ 領域。変換用の静的バッファを共有するため並行呼び出しには対応しない。

#### 実装・検証

- [実装](../../fps/fast-interpolate.hpp)
- [検証: yosupo-polynomial-interpolation-fast.test.cpp](../../verify/verify-yosupo-fps/yosupo-polynomial-interpolation-fast.test.cpp)
