## AVX2 を用いた固定サイズ行列積

`fast_mat_prod_impl` 名前空間の Strassen 法による剰余行列積。現実装のサイズは `S = 1024` に固定されている。

`prod(a, b, c)` に `S*S` 要素の `unsigned int` 配列を渡すと、行優先の行列積 `c = a*b` を書き込む。通常の剰余を入力し、結果も通常の剰余で返す。呼び出し前に対応する Montgomery modint で `mmint::set_mod<mint>()` を設定する。ポインタを SIMD 型として読むため配列には 32 byte のアラインメントを確保し、入出力の領域を重ねない。

`place_s`, `place_t`, `place_rev`, `strassen` は内部のブロック配置用。サイズ変更には定数・作業領域・ブロック条件の確認が必要。一般のサイズではゼロ埋めして固定サイズへ合わせる。

Strassen 部分の演算量は $O(S^{\log_2 7})$、領域 $O(S^2)$。AVX2 対応 CPU が必要で、グローバルな作業領域を共有するため並行呼び出しには対応しない。

#### 実装・検証

- [実装](../../math-fast/mat-prod-strassen.hpp)
- [Verify: matrix-product.cpp](../../tests/unit/math-fast/matrix-product.cpp)
