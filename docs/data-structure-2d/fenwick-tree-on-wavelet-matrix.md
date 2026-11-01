## Wavelet Matrix 上のFenwick Tree

`WaveletMatrix<S,T>` は事前登録した二次元点への加算と半開矩形和を扱う。値型 `T` は零・加減算に対応させる。

`add_point(x,y)` で全更新点を登録して `build()` を一度呼び、`add(x,y,val)` と `sum(L,D,R,U)`（`[L,R) × [D,U)`）で操作する。構築後の未知の点には更新しない。

前処理・領域は $O(n\log n)$、更新・問い合わせは $O(\log^2 n)$。x86 の BMI/POPCNT 系命令を使用する。関連ヘッダと `WaveletMatrix`・`bit_vector` の名前が重なるため、実装を選んで include する。

#### 実装・検証

- [実装](../../data-structure-2d/fenwick-tree-on-wavelet-matrix.hpp)
- [Verify: wavelet-fenwick.cpp](../../tests/unit/data-structure-2d/wavelet-fenwick.cpp)
