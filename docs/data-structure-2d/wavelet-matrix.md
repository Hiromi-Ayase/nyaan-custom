## Wavelet Matrix

#### 概要

数列に対する様々なクエリを$\mathrm{O}(\log N)$で行えるデータ構造。定数倍も比較的軽い。

二次元クエリの処理に使われることが多く、例えばBITを上に載せることで矩形和・一点加算のクエリを処理できるようになる。[実装](https://nyaannyaan.github.io/library/data-structure-2d/fenwick-tree-on-wavelet-matrix.hpp)　また、bit vectorを平衡二分木に変えることで動的なクエリが処理できるようになる。(未実装…)

#### 使い方

格納する値は非負整数とし、構築する列は非空にする。`int`・`long long` とその符号なし型では型の最大値まで格納できる。検索閾値は負でもよく、0以下の閾値未満の要素数は0となる。問い合わせる添字区間は空でもよい。

- `WaveletMatrix(n)`: 要素数nのWaveletMatrixを生成する。
- `set(i, x)`:　i番目の要素にxを代入する。
- `build()`:　データ構造を構築する。(これ以降`set(i, x)`を呼び出してはいけない。)
- `access(k)`: k番目の要素の値を得る。
- `kth_smallest(l, r, k)`:　`[l, r)`の範囲でk(0-indexed)番目に小さい値を返す。
- `kth_largest(l, r, k)`:　`[l, r)`の範囲でk(0-indexed)番目に大きい値を返す。
- `range_freq(l, r, upper)`: `[l, r)`の範囲でupper未満の要素の個数を返す。
- `prev_value(l, r, lower)`: `l, r`の範囲でupper未満の最後の値を返す。
- `next_value(l, r, lower)`: `l, r`の範囲でlower以上の最初の値を返す。

#### 実装・検証

- [実装](../../data-structure-2d/wavelet-matrix.hpp)
- [Verify: wavelet-order-statistics.cpp](../../tests/unit/data-structure-2d/wavelet-order-statistics.cpp)
