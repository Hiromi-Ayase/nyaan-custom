## 多次元 Fourier 変換

`MultidimensionalFourierTransform<T>(base, f)` は各軸の長さ `base` と 1 次元変換 `f(vector<T>&, bool rev)` を受け取る。`fft(a, rev = false)` で各軸を順に変換する。

配列の長さは `product(base)`。添字は第 0 軸が最も速く変わる混合基数表現で、`i0 + base[0]*i1 + base[0]*base[1]*i2 + ...` と平坦化する。`operator()(indices)` はこの添字変換を行う。

`base` は非空で各要素は正、積は `int` に収める。逆変換時の正規化は渡した `f` の責任で、このクラスは追加の除算をしない。

全要素数を $N$、軸長を $b_i$、1 次元変換の時間を $F(b_i)$ とすると、時間 $O(\sum_i (N/b_i)F(b_i))$。作業配列は最大の軸長に比例する。

#### 実装・検証

- [実装](../../ntt/multidimensional-ntt.hpp)
- [Verify: multidimensional.cpp](../../tests/unit/ntt/multidimensional.cpp)
