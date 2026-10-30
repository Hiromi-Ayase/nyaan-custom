## 複素数 FFT による畳み込み

`ArbitraryModConvolution::CooleyTukey` の静的関数で複素数 FFT を利用する。

- 整数配列の `multiply(a,b)` は `vector<long long>`、`double` 配列では `vector<double>` を返す。
- `multiply_15bit<MOD>(a,b)` は非負の `int` 配列を基数 `32000` に分けて計算し、法 `MOD` での `vector<int>` を返す。法は加算時に符号付き `int` があふれない範囲（通常 `MOD < 2^30`）とする。
- `multiply_15bit(a,b)` の法省略時は `vector<__uint128_t>` を返す。

入力は両方とも非空にする。FFT は `double` を使うので、整数の返り値でも丸め誤差があり、係数や長さを大きくすれば精度が失われ得る。整数型での積・和の範囲も別途満たす必要がある。厳密な剰余計算が必要なら NTT 版を使う。

時間 $O(N\log N)$、領域 $O(N)$。低水準の `fft` / `ifft` は内部の配列順序と正規化規則を前提とするため、通常は畳み込み API を使う。

#### 実装・検証

- [実装](../../ntt/complex-fft.hpp)
- [検証: complex-fft.test.cpp](../../verify/verify-unit-test/complex-fft.test.cpp)
- [検証: yosupo-convolution-real-fft-15bit.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-real-fft-15bit.test.cpp)
- [検証: yosupo-convolution-real-fft-toom-3.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-real-fft-toom-3.test.cpp)
