## SIMD による部分集合畳み込み

`fast_multiply<mint>(a, b)` は $c[S]=\sum_{T\subseteq S}a[T]b[S\setminus T]$ を計算する。添字を集合のビット表現とみなす。

両配列は同じ長さ $2^d$ で、`0 <= d <= 23`。空配列は不可。係数には内部値 `.a` を持つ対応した Montgomery modint を使い、呼び出し前に `mmint::set_mod<mint>()` を実行する。入力は変更せず、同じ長さの配列を返す。

要素数ごとに分けたゼータ変換・メビウス変換を AVX2 で処理する。時間 $O(d^2 2^d)$、領域 $O(d2^d)$（実装ではランク用の幅を 24 に固定）。AVX2 対応 CPU が必要。

#### 実装・検証

- [実装](../../math-fast/subset-convolution.hpp)
- [Verify: subset-convolution.cpp](../../tests/unit/math-fast/subset-convolution.cpp)
