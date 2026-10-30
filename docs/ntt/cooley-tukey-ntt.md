## 任意長の数論変換

`ArbitraryLengthNTT<mint>(len = -1)` は 2 冪以外の長さを扱う NTT。法 $p$ は素数とし、長さは `p-1` の約数を使う。

- 構築時の `len` は、それ以上で `p-1` を割り切る最初の値へ切り上げる。省略すると `p-1` となり、大きい法では巨大な表を作るので必要な長さを明示する。
- `ntt(a)` と `intt(a)` は、設定した `len` の約数の長さの配列を直接変換する。逆変換は正規化済み。
- `multiply(a,b)` は `len` の約数へゼロ埋めして畳み込む。入力は非空、結果長は `len` 以下にする。

合成数長は Cooley–Tukey で分解し、小さい素数長は直接計算、大きい素数長は Rader 法を使う。実際の時間は長さの因数分解と内部の畳み込みに依存する。原始根の表には $O(len)$ 領域を使う。

`len` の指定は `1..p-1` とし、変換の利用中に法や設定長を変更しない。内部にキャッシュと参照を保持するため、`set_len` を使った再利用や異なる法を同じ型で切り替える利用には注意が必要。

#### 実装・検証

- [実装](../../ntt/cooley-tukey-ntt.hpp)
- [検証: yosupo-convolution-arbitrarylengthntt.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-arbitrarylengthntt.test.cpp)
