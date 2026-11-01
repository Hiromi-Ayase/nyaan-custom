## 素数長の Rader 変換

`RaderNTT<mint>(p, len, w)` は素数長 `p` の DFT を通常の畳み込みへ帰着する。`ntt(a)` は長さ `p` の配列を直接変換する。

`len` は `p` の倍数で、`w[i]` は長さ `len` の原始根の `i` 乗を並べた表。表を参照で保持するため、オブジェクトの利用中は元の表を存続させる。係数体に必要な根が存在し、内部の `ArbitraryNTT` の長さ・係数上限も満たす必要がある。

添字 `1..p-1` を原始根の指数に置き換えて長さ `p-1` の巡回畳み込みを行う。時間 $O(p\log p)$、領域 $O(p)$。逆変換の正規化は行わない。通常は `ArbitraryLengthNTT` の内部部品として使う。

#### 実装・検証

- [実装](../../ntt/rader-ntt.hpp)
- [Verify: arbitrary-length.cpp](../../tests/unit/ntt/arbitrary-length.cpp)
