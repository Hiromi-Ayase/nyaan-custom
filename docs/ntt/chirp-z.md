## 等比数列上の多項式評価

`ChirpZ(f, W, N = -1, A = 1)` は $f(AW^0),f(AW^1),\ldots,f(AW^{N-1})$ を返す。`f` は低次順の係数列で、省略時の `N` は `f.size()`。

`N >= 0` とし、`W != 0` の場合は `W` の逆元が必要。`W = 0` は最初の値が `f(A)`、以降が `f(0)` となるよう特別に扱う。空多項式や `N = 0` にも対応する。

係数列の型には多項式としての `operator*` が必要で、FPS の積を提供するバックエンドを読み込んでおく。Bluestein の変換により 1 回の畳み込みへ帰着する。長さを $M$ とすると、高速な畳み込みで時間 $O((M+N)\log(M+N))$、領域 $O(M+N)$。

#### 実装・検証

- [実装](../../ntt/chirp-z.hpp)
- [検証: yosupo-convolution-chirp-z.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-chirp-z.test.cpp)
- [検証: yosupo-multipoint-evaluation-chirp-z.test.cpp](../../verify/verify-yosupo-ntt/yosupo-multipoint-evaluation-chirp-z.test.cpp)
